/* $Id$ */
#include<pg_config.h>
#include<libpq-fe.h>
#include"pgsql-drvng.h"
#include<xvr2/DebugConsole.h>
#include<xvr2/StringBuffer.h>

using namespace xvr2;
//using namespace xvr2::Exception;

//////// INSTANCE CREATION AND DESTRUCTION STARTS HERE /////////

PostgreSQLDriver *create_dbdriver_instance(){
#ifdef USE_DEBUG
	PostgreSQLDriver *p = 0;
	p = new PostgreSQLDriver();
	return p;
#else
	return new PostgreSQLDriver();
#endif
}

void destroy_dbdriver_instance(PostgreSQLDriver *obj){
	delete obj;
}

//////// INSTANCE CREATION AND DESTRUCTION ENDS HERE /////////


//////// SUPPORT CLASSES AND FUNCTIONS STARTS HERE /////////
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
				debugConsole << "Unable to retrieve datatype mappings\n";
#endif
				throw DB::SQLQueryException();
			}
			else{
				n = PQntuples(result);
				if(n <= 0)
					throw Exception();
				tmapping = new __type_map[32];
				for(i = 0, j = 0; i < n; i++){
					o = strtol(PQgetvalue(result, i, 0), (char **)NULL, 10);
					typname = PQgetvalue(result, i, 1);
					have_type = false;
					if(strcasecmp(typname, "bool") == 0){
						ltype = DB::Field::BIT;
						have_type = true;
					}
					else if(strcasecmp(typname, "char") == 0){
						ltype = DB::Field::CHAR;
						have_type = true;
					}
					else if(strcasecmp(typname, "int2") == 0){
						ltype = DB::Field::TINYINT;
						have_type = true;
					}
					else if(strcasecmp(typname, "int4") == 0){
						ltype = DB::Field::INTEGER;
						have_type = true;
					}
					else if(strcasecmp(typname, "int8") == 0){
						ltype = DB::Field::BIGINT;
						have_type = true;
					}
					else if(strcasecmp(typname, "float4") == 0){
						ltype = DB::Field::FLOAT;
						have_type = true;
					}
					else if(strcasecmp(typname, "float8") == 0){
						ltype = DB::Field::DOUBLE;
						have_type = true;
					}
					else if(strcasecmp(typname, "varchar") == 0){
						ltype = DB::Field::VARCHAR;
						have_type = true;
					}
					else if(strcasecmp(typname, "text") == 0){
						ltype = DB::Field::TEXT;
						have_type = true;
					}
					else if(strcasecmp(typname, "time") == 0 || strcasecmp(typname, "timetz") == 0){
						ltype = DB::Field::TIME;
						have_type = true;
					}
					else if(strcasecmp(typname, "date") == 0){
						ltype = DB::Field::DATE;
						have_type = true;
					}
					else if(strcasecmp(typname, "timestamp") == 0 || strcasecmp(typname, "timestamptz") == 0){
						ltype = DB::Field::TIMESTAMP;
						have_type = true;
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
//////// SUPPORT CLASSES AND FUNCTIONS ENDS HERE /////////








PostgreSQLDriver::PostgreSQLDriver(){
	dinfo = new DB::DriverInfo(DRV_VERSION, DRV_REVISION, "Juan V. Guerrero", PG_VERSION_STR);
	//Set date format to ISO YYYY-MM-DD HH:MM:SS.M
	putenv("PGDATESTYLE=ISO");
}

PostgreSQLDriver::~PostgreSQLDriver(){
#ifdef USE_DEBUG
	debugConsole << "PotgreSQL driver, cleaning up... \n";
#endif
	delete dinfo;
}

const DB::DriverInfo &PostgreSQLDriver::getVersionInfo(){
	return *dinfo;
}

////////////////////// CONNECT STARTS HERE /////////////////////
void *PostgreSQLDriver::connect(const String &server, const String &__dbname, const String &user, const String &pass, int port){
	//use this method to actually connect to the database via TCP/IP
	PGconn *conn;
	__pgsql_conn *connx;
	String cstr;
	int pport;
	pport = port;
	if(port == 0)
		pport = 5432;
	cstr = "host=";
	cstr += server;
	cstr += " user=";
	cstr += user;
	cstr += " password=";
	cstr += pass;
	cstr += " port=";
	cstr += port;
	cstr += " dbname=";
	cstr += __dbname;
	if(!(conn = PQconnectdb(cstr.toCharPtr()))){
		throw DB::DBConnectionFailed();
		return 0;
	}
	connx = new __pgsql_conn(conn);
	try{
		connx->requestMappings();
	}
	catch(DB::SQLQueryException esql){
		PQfinish(conn);
		throw DB::DBConnectionFailed();
	}
	catch(...){
		PQfinish(conn);
		throw;
	}
	return (void *)connx;

}
////////////////////// CONNECT ENDS HERE /////////////////////

int PostgreSQLDriver::execCommand(void *__conn_handle, const String &command){
	int ret = 0;
	DB::ResultSet *r = 0;
	__pgsql_res *rres;
	/*ResultSet *r = this->query(__conn_handle, command);
	ret = r->affectedRows();
	delete r;*/
	PGresult *result;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)__conn_handle;
	result = PQexec (conn->conn, command.toCharPtr());
	if(result == NULL){
		throw DB::SQLQueryException(PQerrorMessage (conn->conn), command);
	}
	else{
		String rows;
		switch(PQresultStatus(result)){
			case PGRES_TUPLES_OK:
				ret = PQntuples(result);
				PQclear(result);
			case PGRES_COMMAND_OK: //This is an update or delete type command
				rows = PQcmdTuples(result);
				if(rows.size() > 0){
					ret = rows.toInt();
				}
				PQclear(result);
				break;
			default: //Some sort of extrange error ocurred
				r = new DB::ResultSet(this, (void *)rres, false);
				throw DB::SQLQueryException(PQresultErrorMessage (result), r, command);
		}
	}
	return ret;
}

ResultSet *PostgreSQLDriver::query(void *__conn_handle, const String &command){
	//Function will call and execute a query, also it will pass an instance 
	//of a library self-pointer
	DB::ResultSet *r = 0;
	PGresult *result;
	__pgsql_res *rres;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)__conn_handle;

	//Modify query replacing conflictive characters with escape secuences


	result = PQexec (conn->conn, command.toCharPtr());
	if(result == NULL){
/*#ifdef USE_DEBUG
		std::cerr << "While executing query: \"" << command << "\"... " <<  PQerrorMessage (conn->conn) << std::endl;
#endif*/
		throw DB::SQLQueryException(PQerrorMessage (conn->conn), command);
	}
	else{
		switch(PQresultStatus(result)){
			case PGRES_TUPLES_OK:
				rres = new __pgsql_res(result);
				rres->conn = conn;
				r = new DB::ResultSet(this, (void *)rres, true);
				break;
			case PGRES_COMMAND_OK: //This is an update or delete type command
				r = new DB::ResultSet(this, 0, true, PQntuples(result));
				PQclear(result);
				break;
			default: //Some sort of extrange error ocurred
				r = new DB::ResultSet(this, (void *)rres, false);
				throw DB::SQLQueryException(PQresultErrorMessage (result), r, command);
		}
	}
	return r;
}

bool PostgreSQLDriver::disconnect(void *__conn_handle){
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)__conn_handle;
	PQfinish(conn->conn);
	delete conn;
	return true;
}

void PostgreSQLDriver::setAutoCommit(bool){

}

void PostgreSQLDriver::commit(void *){

}

const int PostgreSQLDriver::numRows(void *__res_handle){
	//Will return the number of rows in a query result
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	return r->row_count;
}

const int PostgreSQLDriver::numCols(void *__res_handle){
	//Will return the number of columns in a query result
	int n = 0;
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	n = PQnfields(r->result);
	return n;
}

Field *PostgreSQLDriver::fetchRow(void *__res_handle){
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
		s[n].drv = this;
		thetype = PQftype(r->result, n);
		data = PQgetvalue(r->result, r->curr_row, n);
		if(PQgetisnull(r->result, r->curr_row, n)){
			s[n].init(r->conn->getLocalType(thetype), (void *)0, PQgetlength(r->result, r->curr_row, n) + 1);
		}
		else{
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
						if(!PQgetisnull(r->result, r->curr_row, n)){
							iint = atol(data);
							s[n].init(xvr2::DB::Field::INTEGER, (void *)&iint, sizeof(Int32));
						}
						else{
							s[n].init(xvr2::DB::Field::INTEGER, 0, sizeof(Int32));
						}
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
	}
	r->curr_row++;
	return s;

}

const bool PostgreSQLDriver::freeResultSet(void *__res_handle){
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	PQclear(r->result);
	delete r;
	return true;
}

const bool PostgreSQLDriver::bulkBegin(void *conn_handle, const char *table, const char *columns, const char *delim){
	bool ret;
	StringBuffer sqlcmd;
	PGresult *result;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)conn_handle;
	//sqlcmd = new char[500 + strlen(table) + strlen(columns) + strlen(delim)];
	//sprintf(sqlcmd, "COPY %s (%s) FROM STDIN WITH DELIMITER '%s'", table, columns, delim);
	sqlcmd << "COPY " << table << " (" << columns << ") FROM STDIN WITH DELIMITER '" << delim << "'";
	result = PQexec (conn->conn, sqlcmd.toString().toCharPtr());
	//xvr2_delete_array(sqlcmd);
	if(result == NULL){
		throw DB::SQLQueryException(PQerrorMessage (conn->conn), sqlcmd.toString());
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

const bool PostgreSQLDriver::bulkAddData(void *conn_handle, const char *data, const char *delim){
	int ret;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)conn_handle;
	ret = PQputCopyData(conn->conn, data, strlen(data));
	if(ret == 1)
		return true;
	else if(ret == -1){
		throw DB::SQLQueryException(PQerrorMessage (conn->conn));
	}
	return false;
}

const bool PostgreSQLDriver::bulkEnd(void *conn_handle){
	int ret;
	PGresult *result;
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)conn_handle;
	ret = PQputCopyEnd(conn->conn, NULL);
	if(ret == 1){
		result = PQgetResult(conn->conn);
		if(result == NULL){
			throw DB::SQLQueryException(PQerrorMessage (conn->conn));
		}
		else {
			if(PQresultStatus(result) == PGRES_COMMAND_OK){
				PQclear(result);
				return true;
			}
			PQclear(result);
		}
	}
	throw DB::SQLQueryException(PQerrorMessage (conn->conn));
	return false;
}

char *PostgreSQLDriver::quoteString(const char *in){
	char *buf;
	int len;
	len = strlen(in);
	buf = new char(len * 2 + 1);
	PQescapeString(buf, in, len);
	return buf;
}

String PostgreSQLDriver::escapeString(const String &s){
	char buf[s.size() * 2 + 1];
	PQescapeString(buf, s.toCharPtr(), s.size());
	return String(buf);
}

String PostgreSQLDriver::escapeString(const String &s, void *__conn_handle){
	__pgsql_conn *conn;
	int e_code;
	char buf[s.size() * 2 + 1];
	conn = (__pgsql_conn *)__conn_handle;
	PQescapeStringConn(conn->conn, buf, s.toCharPtr(), s.size(), &e_code);
	if(e_code != 0){
		//Houston we have a problem
		throw DB::DatabaseException(PQerrorMessage (conn->conn));
	}
	return String(buf);
}

const char *PostgreSQLDriver::errorMessage(void *__conn_handle){
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)__conn_handle;
	return PQerrorMessage(conn->conn);
}

const char *PostgreSQLDriver::resultErrorMessage(void *__res_handle){
//char *PQresultErrorMessage(const PGresult *res);
	__pgsql_res *r;
	r = (__pgsql_res *)__res_handle;
	return PQresultErrorMessage(r->result);
}

const bool PostgreSQLDriver::isConnected(void *__conn_handle){
	__pgsql_conn *conn;
	conn = (__pgsql_conn *)__conn_handle;
	return PQstatus(conn->conn) == CONNECTION_OK ? true : false;
}

const bool PostgreSQLDriver::hasConnPolling(){
	return true;
}

