/*
 * $Id$
 */


#include<pg_config.h>
#include<libpq-fe.h>
#include"pgsql-drv.h"
extern long timezone;

#ifndef DRV_VERSION
#define DRV_VERSION 0
#endif

#ifndef DRV_REVISION
#define DRV_REVISION 1
#endif

using namespace xvr2;

/** This has to be a pointer to the parent Driver object, sometimes it is needed
 *  to have a reference to this data Object */
static xvr2::DB::Driver *me;
static xvr2::DB::DriverInfo *info;


class __type_map {
	public:
		Oid oid;
		int localType;
		char *typeName;

		__type_map(){
			typeName = NULL;
			localType = -1;
		}

		__type_map(Oid o, int l){
			oid = o;
			localType = l;
			typeName = NULL;
		}

		__type_map(Oid o, int l, const char *t){
			oid = o;
			localType = l;
			typeName = strdup(t);
		}
		
		~__type_map(){
			if(typeName != NULL)
				free(typeName);
		}
};

class __pgsql_conn {
	public:
		PGconn *conn;
		__type_map *tmapping;

		__pgsql_conn(PGconn *_conn){
			conn = _conn;
		}

		~__pgsql_conn(){
			delete[] tmapping;
		}

		const int getLocalType(Oid o){
			int i;
			for(i = 0; i < 32; i++){
				if(tmapping[i].typeName == NULL)
					continue;
				if(o == tmapping[i].oid)
					return tmapping[i].localType;
			}
			return DB::Field::CHAR;
		}

		const char *getLocalTypeName(Oid o){
			int i;
			for(i = 0; i < 32; i++){
				if(tmapping[i].typeName == NULL)
					continue;
				if(o == tmapping[i].oid)
					return tmapping[i].typeName;
			}
			return 0;
		}
		
		void requestMappings(){
			PGresult *result;
			char *typname;
			int n, j, i;
			unsigned int o;
			int ltype;
			bool have_type;
			result = PQexec(conn, "select oid,typname from pg_type");
			if(result == NULL){
#ifdef USE_DEBUG
				std::cerr << "Unable to retrieve datatype mappings" << std::endl;
#endif
				throw Exception::SQLQuery();
			}
			else{
				n = PQntuples(result);
				if(n <= 0)
					throw Exception::Exception();
				tmapping = new __type_map[32];
#ifdef USE_DEBUG
				std::cout << "\t\tReading mappings for " << n << " datatypes..." << std::endl;
#endif
				for(i = 0, j = 0; i < n; i++){
					o = strtol(PQgetvalue(result, i, 0), (char **)NULL, 10);
					typname = PQgetvalue(result, i, 1);
					have_type = false;
					if(strcasecmp(typname, "bool") == 0){
						ltype = DB::Field::BIT;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::BIT" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "char") == 0){
						ltype = DB::Field::CHAR;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::CHAR" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "int2") == 0){
						ltype = DB::Field::TINYINT;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::TINYINT" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "int4") == 0){
						ltype = DB::Field::INTEGER;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::INTEGER" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "int8") == 0){
						ltype = DB::Field::BIGINT;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::BIGINT" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "float4") == 0){
						ltype = DB::Field::FLOAT;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::FLOAT" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "float8") == 0){
						ltype = DB::Field::DOUBLE;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::DOUBLE" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "varchar") == 0){
						ltype = DB::Field::VARCHAR;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::VARCHAR" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "text") == 0){
						ltype = DB::Field::TEXT;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::TEXT" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "time") == 0 || strcasecmp(typname, "timetz") == 0){
						ltype = DB::Field::TIME;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::TIME" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "date") == 0){
						ltype = DB::Field::DATE;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::DATE" << std::endl;
#endif
					}
					else if(strcasecmp(typname, "timestamp") == 0 || strcasecmp(typname, "timestamptz") == 0){
						ltype = DB::Field::TIMESTAMP;
						have_type = true;
#ifdef USE_DEBUG
						std::cout << "\t\t\t" << typname << "=DB::Field::TIMESTAMP" << std::endl;
#endif
					}

					if(have_type){
						tmapping[j].oid = o;
						tmapping[j].typeName = strdup(typname);
						tmapping[j].localType = ltype;
						j++;
					}
				}
				PQclear(result);
			}
		}
};

class __pgsql_res {
	public:
		PGresult *result;
		__pgsql_conn *conn;
		int curr_row;
		int row_count;
		__pgsql_res(PGresult *r){
			result = r;
			curr_row = 0;
			row_count = PQntuples(result);
		}
};

xvr2::Mutex __sqlGlobalMutex;

void _init(){
	//Default library loading function
	me = 0;
#ifdef USE_DEBUG
	std::cout << "Loading $Id$" << std::endl;
#endif
}

bool	__drv_init(DB::Driver *__me){
	//Execute driver initialization routines in here
	if(__me == 0)
		throw Exception::NullPointer();
	me = __me;
	info = new DB::DriverInfo(DRV_VERSION, DRV_REVISION, "Juan V. Guerrero", PG_VERSION_STR);
	//Set date format to ISO YYYY-MM-DD HH:MM:SS.M
	putenv("PGDATESTYLE=ISO");
#ifdef USE_DEBUG
	std::cout << "PGDATESTYLE=" << getenv("PGDATESTYLE") << std::endl;
#endif
	return true;
}

bool	__drv_cleanup(){
	//Cleanup any state variables and or other remaining data
	std::cout << "PotgreSQL driver, cleaning up... " << std::endl;
	xvr2_delete(info);
	return true;
}

void *__drv_connect(const char *srvr, const char *dbname, const char *usr, const char *pass, const int port){
	//use this method to actually connect to the database via TCP/IP
	PGconn *conn;
	__pgsql_conn *connx;
	String cstr;
	int pport;
	pport = port;
	if(port == 0)
		pport = 5432;
	__sqlGlobalMutex.lock();
	cstr = "host=";
	cstr += srvr;
	cstr += " user=";
	cstr += usr;
	cstr += " password=";
	cstr += pass;
	cstr += " port=";
	cstr += port;
	cstr += " dbname=";
	cstr += dbname;
	if(!(conn = PQconnectdb(cstr.toCharPtr()))){
		__sqlGlobalMutex.unlock();
		throw Exception::DBConnectionFailed();
		return 0;
	}
	
	__sqlGlobalMutex.unlock();
	connx = new __pgsql_conn(conn);
	try{
		connx->requestMappings();
	}
	catch(Exception::SQLQuery esql){
		PQfinish(conn);
		throw Exception::DBConnectionFailed();
	}
	catch(...){
		PQfinish(conn);
		throw;
	}
	return (void *)connx;
}

UInt32 __drv_disconnect(void *handle){
	//A call to this method will disconnect you from the database
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)handle;
	__sqlGlobalMutex.lock();
	PQfinish(conn->conn);
	xvr2_delete(conn);
	__sqlGlobalMutex.unlock();
	return 1;
}

bool	__drv_getVersionInfo(DB::DriverInfo **i){
	//A call to this function will fill the <b>i</b> variable with some
	//information about the driver itself
	*i = info;
	return true;
}

bool	__drv_commit(void *handle){
	// For SQL-based databases use this command to flush commands to the RDBMS
	// engine
	//PostgreSQL does auto-commit when not dealing with transactions
	return true;
}


DB::ResultSet *__drv_query(void *handle, const char *cmd){
	//Function will call and execute a query, also it will pass an instance 
	//of a library self-pointer
	DB::ResultSet *r = 0;
	PGresult *result;
	__pgsql_res *rres;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)handle;

	//Modify query replacing conflictive characters with escape secuences


	result = PQexec (conn->conn, cmd);
	if(result == NULL){
#ifdef USE_DEBUG
		std::cerr << "While executing query: \"" << cmd << "\"... " <<  PQerrorMessage (conn->conn) << std::endl;
#endif
		throw Exception::SQLQuery();
	}
	else{
		switch(PQresultStatus(result)){
			case PGRES_TUPLES_OK:
				rres = new __pgsql_res(result);
				rres->conn = conn;
				r = new DB::ResultSet(me, (void *)rres, true);
				break;
			case PGRES_COMMAND_OK: //This is an update or delete type command
				r = new DB::ResultSet(me, 0, true, PQntuples(result));
				break;
			default: //Some sort of extrange error ocurred
				r = new DB::ResultSet(me, 0, false);
		}
	}
	return r;
}

bool	__drv_usedb(void *handle, const char *dbname){
	//Will change to an active database
	//There is no equivalent to the SQL USE command
	return true;
}

DB::Field *__drv_fetch_next_row(void *__res_handle){
	//Will fetch the next row in a database
	DB::Field *s = 0;
	char *f;
	char *data;
	unsigned int num, n;
	int thetype;
	bool bdat;
	Int16 tint;
	Int32 iint;
	Int64 bint;
	float float4;
	double float8;
	xvr2::Date *tdate;
	xvr2::Time *ttime;
	xvr2::Timestamp *tstamp;
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	if(r->curr_row >= r->row_count)
		return 0;
	//Get the number of columns
	num = PQnfields(r->result);
	//Allocate the field array
	s = new DB::Field[num];
	//Open a loop to instatiate every data field
	for(n = 0; n < num; n++){
		f = PQfname(r->result, n);
		s[n].setFieldName(f);
		thetype = PQftype(r->result, n);
		data = PQgetvalue(r->result, r->curr_row, n);
		if(PQfformat(r->result, n) == 0){
			//DATA IS TEXT
			switch(r->conn->getLocalType(thetype)){
				case DB::Field::BIT:
					if(data[0] == 't'){
						bdat = true;
						s[n].init(xvr2::DB::Field::BIT, (void *)&bdat, sizeof(bool));
					}
					else{
						bdat = false;
						s[n].init(xvr2::DB::Field::BIT, (void *)&bdat, sizeof(bool));
					}
					break;
				case DB::Field::TINYINT:
					tint = atoi(data);
					s[n].init(xvr2::DB::Field::TINYINT, (void *)&tint, sizeof(Int16));
					break;
				case DB::Field::INTEGER:
					iint = atol(data);
					s[n].init(xvr2::DB::Field::INTEGER, (void *)&iint, sizeof(Int32));
					break;
				case DB::Field::BIGINT:
					bint = atoll(data);
					s[n].init(xvr2::DB::Field::BIGINT, (void *)&bint, sizeof(Int64));
					break;
				case DB::Field::FLOAT:
					float4 = atof(data);
					s[n].init(xvr2::DB::Field::FLOAT, (void *)&float4, sizeof(float));
					break;
				case DB::Field::DOUBLE:
					float8 = atof(data);
					s[n].init(xvr2::DB::Field::DOUBLE, (void *)&float8, sizeof(double));
					break;
				case DB::Field::DATE:
					if(!PQgetisnull(r->result, r->curr_row, n))
						tdate = new Date("%Y-%m-%d", data);
					else
						tdate = 0;
					s[n].init(xvr2::DB::Field::DATE, (void *)tdate, sizeof(xvr2::Date));
					xvr2_delete(tdate);
					break;
				case DB::Field::TIME:
					if(!PQgetisnull(r->result, r->curr_row, n))
						ttime = new Time(data);
					else
						ttime = 0;
					s[n].init(xvr2::DB::Field::TIME, (void *)ttime, sizeof(xvr2::Time));
					xvr2_delete(ttime);
					break;
				case DB::Field::TIMESTAMP:
					if(!PQgetisnull(r->result, r->curr_row, n))
						tstamp = new Timestamp("%Y-%m-%d %T", data);
					else
						tstamp = 0;
					s[n].init(xvr2::DB::Field::TIMESTAMP, (void *)tstamp, sizeof(xvr2::Timestamp));
					xvr2_delete(tstamp);
					break;
				case DB::Field::VARCHAR:
				default:
					if(PQgetisnull(r->result, r->curr_row, n))
						s[n].init(xvr2::DB::Field::VARCHAR, (void *)0, PQgetlength(r->result, r->curr_row, n) + 1);
					else
						s[n].init(xvr2::DB::Field::VARCHAR, (void *)data, PQgetlength(r->result, r->curr_row, n) + 1);
			}
		}
		else{
			//DATA IS BINARY
			s[n].init(xvr2::DB::Field::BLOB, (void *)data, PQgetlength(r->result, r->curr_row, n));
		}
	}
	r->curr_row++;
	return s;
}

int	__drv_numcols(void *__res_handle){
	//Will return the number of columns in a query result
	int n = 0;
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	n = PQnfields(r->result);
	return n;
}

int	__drv_numrows(void *__res_handle){
	//Will return the number of rows in a query result
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	return r->row_count;
}

bool	__drv_free_resultset(void *__res_handle){
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	PQclear(r->result);
	delete r;
	return true;
}

bool	__drv_bulk_begin(void *conn_handle, const char *table, const char *columns, const char *delim){
	bool ret;
	char *sqlcmd;
	PGresult *result;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)conn_handle;
	sqlcmd = new char[500 + strlen(table) + strlen(columns) + strlen(delim)];
	sprintf(sqlcmd, "COPY %s (%s) FROM STDIN WITH DELIMITER '%s'", table, columns, delim);
	result = PQexec (conn->conn, sqlcmd);
	xvr2_delete_array(sqlcmd);
	if(result == NULL){
#ifdef USE_DEBUG
		std::cerr << "COPY command failure!!! " <<  PQerrorMessage (conn->conn) << std::endl;
#endif
		throw Exception::SQLQuery();
	}
	switch(PQresultStatus(result)){
		case PGRES_TUPLES_OK:
		case PGRES_COMMAND_OK:
		case PGRES_COPY_IN:
			ret = true;
			break;
		default:
			ret = false;
	}
	PQclear(result);
	return ret;
}

bool	__drv_bulk_insert(void *conn_handle, const char *data, const char *delim){
	int ret;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)conn_handle;
	ret = PQputCopyData(conn->conn, data, strlen(data));
	if(ret == 1)
		return true;
	else if(ret == -1){
#ifdef USE_DEBUG
		std::cerr << "COPY command failure: " <<  PQerrorMessage (conn->conn) << std::endl;
#endif
		throw Exception::SQLQuery();
	}
	return false;
}

bool	__drv_bulk_end(void *conn_handle){
	int ret;
	PGresult *result;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)conn_handle;
	ret = PQputCopyEnd(conn->conn, NULL);
	if(ret == 1){
		result = PQgetResult(conn->conn);
		if(result == NULL){
#ifdef USE_DEBUG
			std::cerr << "COPY command failure: " <<  PQerrorMessage (conn->conn) << std::endl;
#endif
			throw Exception::SQLQuery();
		}
		else {
			if(PQresultStatus(result) == PGRES_COMMAND_OK){
				PQclear(result);
				return true;
			}
			PQclear(result);
		}
	}
#ifdef USE_DEBUG
	std::cerr << "COPY command failure: " <<  PQerrorMessage (conn->conn) << std::endl;
#endif
	throw Exception::SQLQuery();
	return false;
}

char *__drv_quote_string(const char *in){
//size_t PQescapeString (char *to, const char *from, size_t length);
	char *buf;
	int len;
	len = strlen(in);
	buf = new char(len * 2 + 1);
	PQescapeString(buf, in, len);
	return buf;
}

char *__drv_error_message(void *handle){
//char *PQerrorMessage(const PGconn* conn);
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)handle;
	return PQerrorMessage(conn->conn);
}

bool __drv_connected(void *handle){
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)handle;
	return PQstatus(conn->conn) == CONNECTION_OK ? true : false;
}

char *__drv_result_error_message(void *__res_handle){
//char *PQresultErrorMessage(const PGresult *res);
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	return PQresultErrorMessage(r->result);
}
