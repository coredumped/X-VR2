/*
 * $Id$
 */


#include<mysql/mysql.h>
#include<mysql/errmsg.h>
#include<mysql/mysqld_error.h>
#include<mysql-drv.h>

#ifndef DRV_VERSION
#define DRV_VERSION 0
#endif

#ifndef DRV_REVISION
#define DRV_REVISION 1
#endif

using namespace xvr2;

/** This has to be a pointer to the parent Driver object, sometimes it is needed
 *  to have a reference to this data Object */
static DB::Driver *me;
static DB::DriverInfo *info;
static MYSQL mysql_hdlr;

xvr2::Mutex __sqlGlobalMutex;

void _init(){
	//Default library loading function
	me = 0;
	std::cout << "Loading $Id$" << std::endl;
}

bool	__drv_init(DB::Driver *__me){
	//Execute driver initialization routines in here
	if(__me == 0)
		throw Exception::NullPointer();
	me = __me;
	mysql_init(&mysql_hdlr);
	info = new DB::DriverInfo(DRV_VERSION, DRV_REVISION, "Juan V. Guerrero", mysql_get_client_info());
	return true;
}

bool	__drv_cleanup(){
	//Cleanup any state variables and or other remaining data
	std::cout << "MySQL driver, cleaning up... " << std::endl;
	xvr2_delete(info);
	return true;
}

void *__drv_connect(const char *srvr, const char *dbname, const char *usr, const char *pass, const int port){
	//use this method to actually connect to the database via TCP/IP
	MYSQL *conn;
	int pport;
	pport = port;
	if(port == 0)
		pport = 3306;
	__sqlGlobalMutex.lock();
	mysql_init(&mysql_hdlr);
	if(!(conn = mysql_real_connect(&mysql_hdlr, srvr, usr, pass, 0, pport, 0, 0))){
		#ifdef USE_DEBUG
		std::cerr << mysql_error(&mysql_hdlr) << std::endl;
		#endif
		__sqlGlobalMutex.unlock();
		throw Exception::DBConnectionFailed();
		return 0;
	}
	__sqlGlobalMutex.unlock();
	try{
		__drv_usedb((void *)conn, dbname);
	}
	catch(...){
		__drv_disconnect((void *)conn);
		throw;
	}
	return (void *)conn;
}

UInt32 __drv_disconnect(void *handle){
	//A call to this method will disconnect you from the database
	MYSQL *conn;
	conn = (MYSQL *)handle;
	__sqlGlobalMutex.lock();
	mysql_close(conn);
	__sqlGlobalMutex.unlock();
#if ( MYSQL_VERSION_ID >= 41000 )
	mysql_thread_end();
#endif
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
#if ( MYSQL_VERSION_ID >= 41000 )
	if(mysql_commit((MYSQL *)handle) != 0){
		throw Exception::Database();
		return false;
	}
#endif
	return true;
}

DB::ResultSet *__drv_query(void *handle, const char *cmd){
	//Function will call and execute a query, also it will pass an instance 
	//of a library self-pointer
	DB::ResultSet *r = 0;
	int qret;
	MYSQL_RES *result;

	//Modify query replacing conflictive characters with escape secuences

	qret = mysql_query((MYSQL *)handle, cmd);
	if(qret != 0){
#ifdef USE_DEBUG
		std::cerr << "While executing query: \"" << cmd << "\"... " << mysql_error((MYSQL *)handle) << std::endl;
#endif
		switch(qret){
			case CR_SERVER_LOST:
			case CR_SERVER_GONE_ERROR:
				throw Exception::SQLQueryRDBMSDisconnected();
				break;
			default:
				if(mysql_errno((MYSQL *)handle) == ER_PARSE_ERROR)
					throw Exception::UnableToParseQuery();
				else
					throw Exception::SQLQuery();
		};
	}
	else{
		if((result = mysql_store_result((MYSQL *)handle))){
			//Create a resultset to retrieve all data rows
			r = new DB::ResultSet(me, (void *)result, true);
		}
		else{
			//Verify if this is a result comming from a select or 
			//another query type 
			if(mysql_field_count((MYSQL *)handle) == 0){
				//This is not a select, just query the number of 
				//affected rows 
				r = new DB::ResultSet(me, 0, true, mysql_affected_rows((MYSQL *)handle));
			}
			else{
				//How come this is not an sql query, is it an error?
				//throw SQLQueryException();
				r = new DB::ResultSet(me, 0, false);
			}
		}
	}
	return r;
}

bool	__drv_usedb(void *handle, const char *dbname){
	//Will change to an active database
	int retcode;
	if((retcode = mysql_select_db((MYSQL *)handle, dbname)) != 0){
		switch(retcode){
			case CR_SERVER_GONE_ERROR:
			case CR_SERVER_LOST:
				throw Exception::ServerDisconnected();
				break;
			default:
				throw Exception::Database();
		};
		return false;
	}
	return true;
}

DB::Field *__drv_fetch_next_row(void *__res_handle){
	//Will fetch the next row in a database
	DB::Field *s = 0;
	MYSQL_ROW row;
	MYSQL_FIELD *f = 0;
	unsigned int num, n;
	int thetype;
	//Get the number of columns
	num = mysql_num_fields((MYSQL_RES *)__res_handle);
	//Allocate the field array
	s = new DB::Field[num];
	//Get the ResultSet row
	row = mysql_fetch_row((MYSQL_RES *)__res_handle);
	if(row == 0)
		return 0;
	//Open a loop to instatiate every data field
	for(n = 0; n < num; n++){
		f = mysql_fetch_field((MYSQL_RES *)__res_handle);
		s[n].setFieldName(f->name);
		thetype = f->type;
		switch(thetype){
			/*case FIELD_TYPE_BLOB:
				s[n].init(xvr2::DB::Field::BLOB, (void *)(row[n]), f->length + 1);
				break;*/
			case FIELD_TYPE_TINY:
				Int16 tmpt1;
				tmpt1 = atoi((char *)(row[n]));
				s[n].init(xvr2::DB::Field::TINYINT, &tmpt1, sizeof(Int16));
				break;
			case FIELD_TYPE_SHORT:
			case FIELD_TYPE_INT24:
			case FIELD_TYPE_LONG:
				Int32 tmpt2;
				tmpt2 = atoi((char *)(row[n]));
				s[n].init(xvr2::DB::Field::INTEGER, &tmpt2, sizeof(Int32));
				break;
			case FIELD_TYPE_LONGLONG:
				Int64 nlong;
				nlong = atoll((char *)(row[n]));
				s[n].init(xvr2::DB::Field::BIGINT, &nlong, sizeof(Int64));
				break;
			case FIELD_TYPE_FLOAT:
				float nfloat;
				nfloat = atof((char *)(row[n]));
				s[n].init(xvr2::DB::Field::FLOAT, &nfloat, sizeof(float));
				break;
			case FIELD_TYPE_DOUBLE:
				double ndouble;
				ndouble = atof((char *)(row[n]));
				s[n].init(xvr2::DB::Field::DOUBLE, &ndouble, sizeof(double));
				break;
			case FIELD_TYPE_TIME:
				Time *ttime;
				ttime = new Time((char *)(row[n]));
				s[n].init(xvr2::DB::Field::TIME, ttime, sizeof(xvr2::Time));
				xvr2_delete(ttime);
				break;
			case FIELD_TYPE_DATE:
				Date *ddate;
				ddate = new Date("%Y-%m-%d", (char *)(row[n]));
				s[n].init(xvr2::DB::Field::DATE, ddate, sizeof(xvr2::Date));
				xvr2_delete(ddate);
				break;
			case FIELD_TYPE_DATETIME:
				Date *tdate;
				tdate = new Date("%Y-%m-%d %T", (char *)(row[n]));
				s[n].init(xvr2::DB::Field::DATE, tdate, sizeof(xvr2::Date));
				xvr2_delete(tdate);
				break;
			case FIELD_TYPE_TIMESTAMP:
				Timestamp *tdate1;
				tdate1 = new Timestamp("%Y%m%d%H%M%S", (char *)(row[n]));
				s[n].init(xvr2::DB::Field::TIMESTAMP, tdate1, sizeof(xvr2::Timestamp));
				xvr2_delete(tdate1);
				break;
			default:
				s[n].init(xvr2::DB::Field::VARCHAR, (void *)(row[n]), f->length);
				break;
		}
	}
	mysql_field_seek((MYSQL_RES *)__res_handle, 0);
	return s;
}

int	__drv_numcols(void *__res_handle){
	//Will return the number of columns in a query result
	int n = 0;
	n = mysql_num_fields((MYSQL_RES *)__res_handle);
	return n;
}

int	__drv_numrows(void *__res_handle){
	//Will return the number of rows in a query result
	int n = 0;
	n = mysql_num_rows((MYSQL_RES *)__res_handle);
	return n;
}

bool	__drv_free_resultset(void *__res_handle){
	mysql_free_result((MYSQL_RES *)__res_handle);
	return true;
}
