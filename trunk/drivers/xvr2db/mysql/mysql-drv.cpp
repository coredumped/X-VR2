/* $Id$*/
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include<mysql/mysql.h>
#include<mysql/errmsg.h>
#include<xvr2/ThreadManager.h>
#include<xvr2/FinalizerCallback.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/SharedVar.h>
#include<xvr2/Timestamp.h>
#include<xvr2/RawOutputStream.h>
#include<cerrno>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"mysql-drv.h"

using namespace xvr2;
//using namespace xvr2::Exception;

//////// INSTANCE CREATION AND DESTRUCTION STARTS HERE /////////

static void __initialize_mysql(){
	my_init();
}

MySQLDriver *create_dbdriver_instance(){
	static pthread_once_t __mysql_inited = PTHREAD_ONCE_INIT;
	pthread_once(&__mysql_inited, __initialize_mysql);
	return new MySQLDriver();
}

void destroy_dbdriver_instance(MySQLDriver *obj){
	delete obj;
}

//////// INSTANCE CREATION AND DESTRUCTION ENDS HERE /////////


//////// SUPPORT CLASSES AND FUNCTIONS STARTS HERE /////////

class MySQLThreadCleanupFinalizer : public FinalizerCallback {
	public:
		void operator()(){
			mysql_thread_end();
		}
};

class __data_uploader : public xvr2::BackgroundFunction {
	private:
	protected:
	public:
		String cmd;
		MYSQL *conn;
		SharedVar<bool> failed;
		int err_code;
		String error_msg;
		__data_uploader(){
			failed = false;
		}
		__data_uploader(MYSQL *_conn){
			conn = _conn;
			failed = false;
		}
		__data_uploader(MYSQL *_conn, const String &s){
			cmd = s;
			conn = _conn;
			failed = false;
		}
		__data_uploader(const String &s){
			cmd = s;
			failed = false;
		}
		void setCmd(const String &c){
			cmd = c;
		}
		void operator()(){
			failed = false;
			mysql_thread_init();
			int ok = mysql_query(conn, cmd.toCharPtr());
			if(ok != 0){
				failed = true;
				err_code = mysql_errno(conn);
				error_msg = mysql_error(conn);
			}
			else {
				failed = false;
			}
			mysql_thread_end();
		}
};

class __rdbms_conn {
	public:
		MYSQL *conn;
		UInt64 creator_tid;
		SharedVar<bool> is_loading_data;
		String fifo;
		int fifo_fd;
		RawOutputStream pipeline;
		__data_uploader data_upload;

		__rdbms_conn(MYSQL *_conn){
			conn = _conn;
			data_upload.conn = conn;
			creator_tid = ThreadManager::getCurrentThreadID();
			is_loading_data = false;
		}

		~__rdbms_conn(){
			//Release connection structure resources here
		}

};

class __rdbms_result_set {
	public:
		MYSQL_RES *result;
		__rdbms_conn *conn;
		int curr_row;
		int row_count;
		__rdbms_result_set(MYSQL_RES *r){
			result = r;
			curr_row = 0;
			row_count = mysql_num_rows(r);/* Insert funtion name that retrieves the 
				        amount of rows contained in this
				        resultset. */
		}
};
//////// SUPPORT CLASSES AND FUNCTIONS ENDS HERE /////////


MySQLDriver::MySQLDriver(){
	dinfo = new DB::DriverInfo(DRV_VERSION, DRV_REVISION, "Juan V. Guerrero <mindstorm2600 at users dot sourceforge dot net>", mysql_get_client_info());
	// Call any initialization routines needed by the underlying
	// RDBMS library to be wrapped
#if defined (__linux) || defined (__linux__) || defined (linux__) || defined (linux) || defined (USING_LINUX)
	conn_requires_lock = false;
#else
	conn_requires_lock = true;
#endif
	query_requires_lock = true;
}

MySQLDriver::~MySQLDriver(){
	delete dinfo;
}

const DB::DriverInfo &MySQLDriver::getVersionInfo(){
	return *dinfo;
}

////////////////////// CONNECT STARTS HERE /////////////////////
void *MySQLDriver::connect(const String &server, const String &__dbname, const String &user, const String &pass, int port){
	//use this method to actually connect to the database via TCP/IP
	MYSQL *conn;
	__rdbms_conn *connx;
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, server.toCharPtr(), user.toCharPtr(), pass.toCharPtr(), __dbname.toCharPtr(), port, NULL, 0);
	connx = new __rdbms_conn(conn);
	return (void *)connx;

}
////////////////////// CONNECT ENDS HERE /////////////////////


int MySQLDriver::execCommand(void *__conn_handle, const xvr2::String &command){
	int r = 0;
	MYSQL_RES *result;
	__rdbms_result_set *rres;
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	//Verify that MySQL's TSD is in place before attemtping to run the query
	if(conn->creator_tid != ThreadManager::getCurrentThreadID()){
		if(mysql_thread_init() == 0){
			//Install finalization handler here
			if(!ThreadManager::currentIsMain()){
				if(ThreadManager::currentIsThread()){
					ThreadManager::getCurrentThread()->registerFinalizer(new MySQLThreadCleanupFinalizer());
				}
				else if(ThreadManager::currentIsBackgroundFunction()){
					ThreadManager::getCurrentBackgroundFunction()->registerFinalizer(new MySQLThreadCleanupFinalizer());
				}
			}
		}
	}

	int queryid = mysql_query(conn->conn, command.toCharPtr());
	if(queryid != 0){
		switch(queryid){
			case CR_SERVER_GONE_ERROR:
				throw DB::DBConnectionFailed();
				break;
			case CR_SERVER_LOST:
				throw DB::DBConnectionFailed();
				break;
			case CR_COMMANDS_OUT_OF_SYNC:
			case CR_UNKNOWN_ERROR:
				throw DB::SQLQueryException(mysql_error(conn->conn), command);
				break;
		}
	}
	r = mysql_field_count(conn->conn);
	return r;
}

ResultSet *MySQLDriver::query(void *__conn_handle, const String &command){
	DB::ResultSet *r = 0;
	MYSQL_RES *result;
	__rdbms_result_set *rres;
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	//Verify that MySQL's TSD is in place before attemtping to run the query
	if(conn->creator_tid != ThreadManager::getCurrentThreadID()){
		if(mysql_thread_init() == 0){
			//Install finalization handler here
			if(!ThreadManager::currentIsMain()){
				if(ThreadManager::currentIsThread()){
					ThreadManager::getCurrentThread()->registerFinalizer(new MySQLThreadCleanupFinalizer());
				}
				else if(ThreadManager::currentIsBackgroundFunction()){
					ThreadManager::getCurrentBackgroundFunction()->registerFinalizer(new MySQLThreadCleanupFinalizer());
				}
			}
		}
	}

	int queryid = mysql_query(conn->conn, command.toCharPtr());
	if(queryid != 0){
		switch(queryid){
			case CR_COMMANDS_OUT_OF_SYNC:
			case CR_SERVER_GONE_ERROR:
			case CR_SERVER_LOST:
			case CR_UNKNOWN_ERROR:
				throw DB::SQLQueryException(mysql_error(conn->conn), command);
				break;
		}
	}
	result = mysql_store_result(conn->conn);
	if(result == NULL){
		//Could have been an UPDATE/DELETE/INSERT
		if(mysql_field_count(conn->conn) > 0){
				r = new DB::ResultSet(this, 0, true, mysql_affected_rows(conn->conn));
		}
		else{
				throw DB::SQLQueryException(mysql_error(conn->conn), command);
		}
	}
	else{
		//Result set is from a select statement
		/* Analyze resultset status */
		rres = new __rdbms_result_set(result);
		rres->conn = conn;
		r = new DB::ResultSet(this, (void *)rres, true);
	}
	return r;
}

bool MySQLDriver::disconnect(void *__conn_handle){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	/* CLOSE RDBMS CONNECTION */(conn->conn);
	delete conn;
	return true;
}

void MySQLDriver::setAutoCommit(bool){
	/* CALL SPECIFIC RDBMS FUNCTION TO SWITCH AUTO-COMMIT ON OR OFF, Oracle (tm) anyone? */
}

void MySQLDriver::commit(void *){
	/* CALL SPECIFIC RDBMS FUNCTION TO COMMIT PREVIOUSLY ISSUED COMMANDS, Oracle (tm) anyone? */
}

const int MySQLDriver::numRows(void *__res_handle){
	//Will return the number of rows in a query result
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	return r->row_count;
}

const int MySQLDriver::numCols(void *__res_handle){
	//Will return the number of columns in a query result
	int n = 0;
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	n = mysql_num_fields(r->result);
	return n;
}

/*
 * MYSQL_TYPE_TINY	TINYINT field
MYSQL_TYPE_SHORT	SMALLINT field
MYSQL_TYPE_LONG	INTEGER field
MYSQL_TYPE_INT24	MEDIUMINT field
MYSQL_TYPE_LONGLONG	BIGINT field

MYSQL_TYPE_DECIMAL	DECIMAL or NUMERIC field
MYSQL_TYPE_FLOAT	FLOAT field
MYSQL_TYPE_DOUBLE	DOUBLE or REAL field

MYSQL_TYPE_TIMESTAMP	TIMESTAMP field
MYSQL_TYPE_DATE	DATE field
MYSQL_TYPE_TIME	TIME field
MYSQL_TYPE_DATETIME	DATETIME field
MYSQL_TYPE_YEAR	YEAR field

MYSQL_TYPE_STRING	CHAR or BINARY field
MYSQL_TYPE_VAR_STRING	VARCHAR or VARBINARY field

MYSQL_TYPE_BLOB	BLOB or TEXT field (use max_length to determine the maximum length)
MYSQL_TYPE_SET	SET field
MYSQL_TYPE_ENUM	ENUM field
MYSQL_TYPE_GEOMETRY	Spatial field (MySQL 4.1.0 and up)
MYSQL_TYPE_NULL	NULL-type field
 */

Field *MySQLDriver::fetchRow(void *__res_handle){
	//Will fetch the next row in a database
	DB::Field *s = 0;
	char *data;
	unsigned int num, n;
	//int thetype;
	Int16 tint;
	Int32 iint;
	Int64 bint;
	float float4;
	double float8;
	xvr2::Date *tdate;
	xvr2::Time *ttime;
	xvr2::Timestamp *tstamp;
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	if(r->curr_row >= r->row_count)
		return 0;
	//Get the number of columns
	num = mysql_num_fields(r->result);
	//Allocate the field array
	s = new DB::Field[num];
	MYSQL_ROW row = mysql_fetch_row(r->result);
	//Open a loop to instatiate every data field
	for(n = 0; n < num; n++){
		MYSQL_FIELD *m_field = mysql_fetch_field_direct(r->result, n);
		s[n].setFieldName(m_field->name);
		//thetype = translate_field_types(m_field->type); /* FIND A WAY TO GET THE FIELD TYPE MATCHING OUR ENUMS */

		/* * * WARNING: data must be a null terminated string!!!!!!! * * */

		//data = /* GET THE VALUE STORED AT THE CURRENT CELL */(r->result, r->curr_row, n);
		data = row[n];
		//DATA IS TEXT
		switch(m_field->type){
			//case DB::Field::TINYINT:
			case MYSQL_TYPE_TINY:
			case MYSQL_TYPE_SHORT:
				if(data == NULL){
					s[n].init(xvr2::DB::Field::TINYINT, (void *)0, sizeof(Int16));
				}
				else{
					tint = atoi(data);
					s[n].init(xvr2::DB::Field::TINYINT, (void *)&tint, sizeof(Int16));
				}
				break;
			//case DB::Field::INTEGER:
			case MYSQL_TYPE_INT24:
			case MYSQL_TYPE_LONG:
				if(data == NULL){
					s[n].init(xvr2::DB::Field::INTEGER, (void *)0, sizeof(Int32));
				}
				else{
					iint = atol(data);
					s[n].init(xvr2::DB::Field::INTEGER, (void *)&iint, sizeof(Int32));
				}
				break;
			//case DB::Field::BIGINT:
			case MYSQL_TYPE_LONGLONG:
				if(data == NULL){
					s[n].init(xvr2::DB::Field::BIGINT, (void *)0, sizeof(Int64));
				}
				else{
					bint = atoll(data);
					s[n].init(xvr2::DB::Field::BIGINT, (void *)&bint, sizeof(Int64));
				}
				break;
			//case DB::Field::FLOAT:
			case MYSQL_TYPE_FLOAT:
				if(data == NULL){
					s[n].init(xvr2::DB::Field::FLOAT, (void *)0, sizeof(float));
				}
				else{
					float4 = atof(data);
					s[n].init(xvr2::DB::Field::FLOAT, (void *)&float4, sizeof(float));
				}
				break;
			//case DB::Field::DOUBLE:
			case MYSQL_TYPE_DOUBLE:
				if(data == NULL){
					s[n].init(xvr2::DB::Field::DOUBLE, (void *)0, sizeof(double));
				}
				else{
					float8 = atof(data);
					s[n].init(xvr2::DB::Field::DOUBLE, (void *)&float8, sizeof(double));
				}
				break;
			//case DB::Field::DATE:
			case MYSQL_TYPE_DATE:
				if(tdate != NULL)
					tdate = new Date("%Y-%m-%d", data);
				else
					tdate = 0;
				s[n].init(xvr2::DB::Field::DATE, (void *)tdate, sizeof(xvr2::Date));
				xvr2_delete(tdate);
				break;
			//case DB::Field::TIME:
			case MYSQL_TYPE_TIME:
				if(data != NULL)
					ttime = new Time(data);
				else
					ttime = 0;
				s[n].init(xvr2::DB::Field::TIME, (void *)ttime, sizeof(xvr2::Time));
				xvr2_delete(ttime);
				break;
			//case DB::Field::TIMESTAMP:
			case MYSQL_TYPE_TIMESTAMP:
			case MYSQL_TYPE_DATETIME:
				if(data != NULL)
					tstamp = new Timestamp("%Y-%m-%d %T", data);
				else
					tstamp = 0;
				s[n].init(xvr2::DB::Field::TIMESTAMP, (void *)tstamp, sizeof(xvr2::Timestamp));
				xvr2_delete(tstamp);
				break;
			//case DB::Field::VARCHAR:
			case MYSQL_TYPE_NULL:
				s[n].init(xvr2::DB::Field::VARCHAR, (void *)0, 0);
				break;
			case MYSQL_TYPE_STRING:
			case MYSQL_TYPE_VAR_STRING:
			default:
				if(data == NULL)
					s[n].init(xvr2::DB::Field::VARCHAR, (void *)0, 0);
				else
					s[n].init(xvr2::DB::Field::VARCHAR, (void *)data, m_field->max_length + 1);
		}
	}
	r->curr_row++;
	return s;

}

const bool MySQLDriver::freeResultSet(void *__res_handle){
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	mysql_free_result(r->result);
	delete r;
	return true;
}

const bool MySQLDriver::bulkBegin(void *conn_handle, const char *table, const char *columns, const char *delim){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)conn_handle;
	//Lock query access!!!
	conn->is_loading_data = true;

	//Create a specific FIFO for this matters
	StringBuffer fifo_file;
	fifo_file << "/tmp/mysql-drv-" << ThreadManager::getCurrentThreadID() << "-" << ((UInt32)getpid()) << ".dat";
	conn->fifo = fifo_file.toString();
	StringBuffer cmd;
	cmd << "LOAD DATA LOCAL INFILE '" << conn->fifo << "' INTO TABLE " << table << " FIELDS TERMINATED BY '" << delim << "' ";
	int ok = mkfifo(conn->fifo.toCharPtr(), 0600);
	if(ok != 0){
		conn->is_loading_data = false;
		throw SystemException(errno);
	}
	conn->pipeline.open(conn->fifo.toCharPtr());
	conn->data_upload.setCmd(cmd.toString());
	conn->data_upload.failed = false;
	ThreadManager::start(conn->data_upload);
	if(conn->data_upload.failed == true){
		conn->pipeline.close();
		throw SQLQueryException(conn->data_upload.error_msg.toCharPtr(), conn->data_upload.cmd);
	}
	return true;
}

const bool MySQLDriver::bulkAddData(void *conn_handle, const char *data, const char *delim){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)conn_handle;
	conn->pipeline << data << delim;
	return true;
}

const bool MySQLDriver::bulkEnd(void *conn_handle){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)conn_handle;
	char e = EOF;
	Timestamp t1;
	conn->pipeline.write(&e, sizeof(char));
	conn->pipeline.close();
	while(conn->data_upload.terminated == false){
		usleep(100);
	conn->is_loading_data = false;
	unlink(conn->fifo.toCharPtr());
	conn->fifo.clear();
	}
	if(conn->data_upload.failed == true){
		throw SQLQueryException(conn->data_upload.error_msg.toCharPtr(), conn->data_upload.cmd);
	}
	conn->data_upload.error_msg.clear();
	conn->data_upload.cmd.clear();
	return true;
}

char *MySQLDriver::quoteString(const char *in){
	char *buf;
	int len;
	len = strlen(in);
	buf = new char(len * 2 + 1);
	mysql_escape_string(buf, in, len);
	return buf;
}

String MySQLDriver::escapeString(const String &s){
	char buf[s.size() * 2 + 1];
	mysql_escape_string(buf, s.toCharPtr(), s.size());
	return String(buf);
}

String MySQLDriver::escapeString(const String &s, void *__conn_handle){
	__rdbms_conn *conn;
	char buf[s.size() * 2 + 1];
	conn = (__rdbms_conn *)__conn_handle;
	mysql_real_escape_string(conn->conn, buf, s.toCharPtr(), s.size());
	return String(buf);
}

const char *MySQLDriver::errorMessage(void *__conn_handle){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	return mysql_error(conn->conn);
}

const char *MySQLDriver::resultErrorMessage(void *__res_handle){
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	return mysql_error(r->conn->conn);
}

const bool MySQLDriver::isConnected(void *__conn_handle){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	mysql_ping(conn->conn);
	if(mysql_errno(conn->conn) == CR_SERVER_GONE_ERROR) return false;
	return true;
}

const bool MySQLDriver::hasConnPolling(){
	/* If there exists a function in thi driver to check connection status */
	return true;
}
