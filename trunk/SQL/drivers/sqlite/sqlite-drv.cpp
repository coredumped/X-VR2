/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#include<sqlite3.h>
#include<sqlite-drv.h>
#include<xvr2/DebugConsole.h>
#include<xvr2/StringBuffer.h>
#include<map>

using namespace xvr2;
//using namespace xvr2::Exception;

//////// INSTANCE CREATION AND DESTRUCTION STARTS HERE /////////

struct dmap_func {
	bool operator()(int s1, int s2) const {
		return (s1 < s2)?true:false;
	}
};

static std::map<int, int, dmap_func> __data_map;

SQLiteDriver *create_dbdriver_instance(){
	__data_map[SQLITE_INTEGER] = SQL::Field::INTEGER;
	__data_map[SQLITE_FLOAT] = SQL::Field::DOUBLE;
	__data_map[SQLITE_TEXT] = SQL::Field::CHAR;
	__data_map[SQLITE_BLOB] = SQL::Field::BLOB;
	__data_map[SQLITE_NULL] = SQL::Field::CHAR;
#ifdef USE_DEBUG
	SQLiteDriver *p = 0;
	p = new SQLiteDriver();
	return p;
#else
	return new SQLiteDriver();
#endif
}

void destroy_dbdriver_instance(SQLiteDriver *obj){
	delete obj;
}

//////// INSTANCE CREATION AND DESTRUCTION ENDS HERE /////////


//////// SUPPORT CLASSES AND FUNCTIONS STARTS HERE /////////

struct __sqlite_conn {
	sqlite3 *conn;
	SQL::DatabaseException::ConnectionParams c_params;
	__sqlite_conn(sqlite3 *_conn, SQL::DatabaseException::ConnectionParams _c_params){
		conn = _conn;
		c_params = _c_params;
	}

	~__sqlite_conn(){
	}
};

class __sqlite_res {
	public:
		__sqlite_conn *conn;
		sqlite3_stmt *statement;
		bool reached_end;
		__sqlite_res(__sqlite_conn *_c, sqlite3_stmt *s){
			conn = _c;
			statement = s;
			reached_end = false;
		}
};
//////// SUPPORT CLASSES AND FUNCTIONS ENDS HERE /////////


SQLiteDriver::SQLiteDriver(){
	dinfo = new SQL::DriverInfo(DRV_VERSION, DRV_REVISION, 
			"Juan V. Guerrero <ryoma dot nagare at gmail dot com>", 
			SQLITE_VERSION);
}

SQLiteDriver::~SQLiteDriver(){
#ifdef USE_DEBUG
	debugConsole << "SQLite driver, cleaning up... \n";
#endif
	delete dinfo;
}

const SQL::DriverInfo &SQLiteDriver::getVersionInfo(){
	return *dinfo;
}

////////////////////// CONNECT STARTS HERE /////////////////////
void *SQLiteDriver::connect(const String &server, const String &__dbname, const String &user, const String &pass, int port){
	throw SQL::DriverOperationNotSupported("connect");
}
void *SQLiteDriver::connect(const String &dbsock, 
				const String &_dbname, const String &_user, 
				const String &_pass){
	throw SQL::DriverOperationNotSupported("connect");
}

void *SQLiteDriver::open(const String &dbfile){
	sqlite3 *conn;
	__sqlite_conn *connx = 0;
	if(sqlite3_open(dbfile.toCharPtr(), &conn) != SQLITE_OK){
		throw SQL::ConnectionFailure(DatabaseException::ConnectionParams(
						DatabaseException::EMBEDDED, "", -1, "", "", "", 
						dbfile.toCharPtr()), sqlite3_errmsg(conn));
	}
	connx = new __sqlite_conn(conn, DatabaseException::ConnectionParams(
						DatabaseException::EMBEDDED, "", -1, "", "", "", 
						dbfile.toCharPtr()));
	return connx;
}
////////////////////// CONNECT ENDS HERE /////////////////////

static const char *__msg_unable_to_lock = "Unable to obtain database lock, "
											"try again later.";

int SQLiteDriver::execCommand(void *__conn_handle, const String &command){
	int ret = -1;
	__sqlite_conn *conn;
	conn = (__sqlite_conn *)__conn_handle;
	sqlite3_stmt *statement;
	char *tail;
	//Prepare statement
	if(sqlite3_prepare_v2(conn->conn, command.toCharPtr(), command.size(), 
			&statement, (const char **)&tail) != SQLITE_OK){
		throw SQL::SQLQueryException(sqlite3_errmsg(conn->conn), command);
	}
	//Evaluate
	switch(sqlite3_step(statement)){
		case SQLITE_DONE:
			ret = sqlite3_changes(conn->conn);
			sqlite3_finalize(statement);
			break;
		case SQLITE_BUSY:
			if(sqlite3_errcode(conn->conn) == SQLITE_OK){
				throw SQL::DatabaseException(__msg_unable_to_lock, conn->c_params);
			}
			else{
				throw SQL::DatabaseException(sqlite3_errmsg(conn->conn), conn->c_params);
			}
			break;
		default:
			throw SQL::SQLQueryException(sqlite3_errmsg(conn->conn), command);
	}
	return ret;
}

ResultSet *SQLiteDriver::query(void *__conn_handle, const String &command){
	SQL::ResultSet *r = 0;
	__sqlite_conn *conn;
	__sqlite_res *_res;
	conn = (__sqlite_conn *)__conn_handle;
	sqlite3_stmt *statement;
	char *tail;
	//Prepare statement
	if(sqlite3_prepare_v2(conn->conn, command.toCharPtr(), command.size(), 
			&statement, (const char **)&tail) != SQLITE_OK){
		throw SQL::SQLQueryException(sqlite3_errmsg(conn->conn), command);
	}
	_res = new __sqlite_res(conn, statement);
	if(sqlite3_column_count(statement) == 0){
		r = new SQL::ResultSet(this, 0, true, sqlite3_changes(conn->conn));
	}
	else{
		r = new SQL::ResultSet(this, (void *)_res, true);
	}
	return r;
}

bool SQLiteDriver::disconnect(void *__conn_handle){
	__sqlite_conn *conn;
	conn = (__sqlite_conn *)__conn_handle;
	sqlite3_close(conn->conn);
	delete conn;
	return true;
}

void SQLiteDriver::setAutoCommit(bool){

}

void SQLiteDriver::commit(void *){

}

const int SQLiteDriver::numRows(void *__res_handle){
	//SQLite does not provide this functionality
	throw SQL::DriverOperationNotSupported("numRows");
	return -1;
}

const int SQLiteDriver::numCols(void *__res_handle){
	//Will return the number of columns in a query result
	int n = 0;
	__sqlite_res *r;
	r = (__sqlite_res *)__res_handle;
	//n = PQnfields(r->result);
	n = sqlite3_column_count(r->statement);
	return n;
}

Field *SQLiteDriver::fetchRow(void *__res_handle){
	//Will fetch the next row in a database
	SQL::Field *s = 0;
	char *data;
	void *blobby;
	unsigned int num, n;
	int thetype;
	int errcode;
	int valx;
	double float8;
	__sqlite_res *r;
	r = (__sqlite_res *)__res_handle;
	
	if(r->reached_end){
		return 0;
	}
	errcode = sqlite3_step(r->statement);
	if(errcode == SQLITE_DONE){
		r->reached_end = true;
		return 0;
	}
	//Get the number of columns
	num = sqlite3_column_count(r->statement);
	//Allocate the field array
	s = new SQL::Field[num];
	//Open a loop to instatiate every data field
	for(n = 0; n < num; n++){
		s[n].setFieldName(sqlite3_column_name(r->statement, n));
		s[n].drv = this;
		thetype = sqlite3_column_type(r->statement, n);
		if(thetype == SQLITE_NULL){
			s[n].init(__data_map[thetype], (void *)0, sqlite3_column_bytes(r->statement, n) + 1);
		}
		else{
			//data = PQgetvalue(r->statement, r->curr_row, n);
			if(thetype == SQLITE_BLOB){
				//DATA IS BINARY
				blobby = (void *)sqlite3_column_blob(r->statement, n);
				s[n].init(xvr2::SQL::Field::BLOB, blobby, sqlite3_column_bytes(r->statement, n));
			}
			else{
				//DATA IS TEXT
				switch(__data_map[thetype]){
					case SQL::Field::INTEGER:
						valx = sqlite3_column_int(r->statement, n);
						s[n].init(xvr2::SQL::Field::INTEGER, (void *)&valx, 
									sizeof(int));
						break;
					case SQL::Field::DOUBLE:
						float8 = sqlite3_column_double(r->statement, n);
						s[n].init(xvr2::SQL::Field::DOUBLE, (void *)&float8, 
									sizeof(double));
						break;
					case SQL::Field::CHAR:
					default:
						data = (char *)sqlite3_column_text(r->statement, n);
						s[n].init(xvr2::SQL::Field::CHAR, (void *)data, sqlite3_column_bytes(r->statement, n));
				}
			}
		}
	}
	return s;

}

const bool SQLiteDriver::freeResultSet(void *__res_handle){
	__sqlite_res *r;
	r = (__sqlite_res *)__res_handle;
	sqlite3_finalize(r->statement);
	delete r;
	return true;
}

const bool SQLiteDriver::bulkBegin(void *conn_handle, const char *table, const char *columns, const char *delim){
	throw SQL::DriverOperationNotSupported("bulkBegin");
	return false;
}

const bool SQLiteDriver::bulkAddData(void *conn_handle, const char *data, const char *delim){
	throw SQL::DriverOperationNotSupported("bulkAddData");
	return false;
}

const bool SQLiteDriver::bulkEnd(void *conn_handle){
	throw SQL::DriverOperationNotSupported("bulkEnd");
	return false;
}

const bool SQLiteDriver::bulkDownloadBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim){
	throw SQL::DriverOperationNotSupported("bulkDownloadBegin");
	return false;
}

const bool SQLiteDriver::bulkDownloadData(void *conn_handle, xvr2::String &data){
	throw SQL::DriverOperationNotSupported("bulkDownloadData");
	return false;
}

const bool SQLiteDriver::bulkDownloadEnd(void *conn_handle){
	throw SQL::DriverOperationNotSupported("bulkDownloadEnd");
	return false;
}

static String __generic_quote(const String &s){
	String tmp;
	char buf[2];
	buf[1] = 0;
	for(UInt32 i = 0; i < s.size(); i++){
		switch(s[i]){
			case 0:
				tmp.concat("\\0");
				break;
			case '\'':
				tmp.concat("''");
				break;
			default:
				buf[0] = s[i];
				tmp.concat(buf);
		}
	}
	return String(tmp);
}

char *SQLiteDriver::quoteString(const char *in){
	throw SQL::DriverOperationNotSupported("quoteString");
	return 0;
}

String SQLiteDriver::escapeString(const String &s){
	return __generic_quote(s);
}

String SQLiteDriver::escapeString(const String &s, void *__conn_handle){
	return __generic_quote(s);
}

const char *SQLiteDriver::errorMessage(void *__conn_handle){
	__sqlite_conn *conn;
	conn = (__sqlite_conn *)__conn_handle;
	return sqlite3_errmsg(conn->conn);
}

const char *SQLiteDriver::resultErrorMessage(void *__res_handle){
	__sqlite_res *r;
	r = (__sqlite_res *)__res_handle;
	return sqlite3_errmsg(r->conn->conn);
}

const bool SQLiteDriver::isConnected(void *__conn_handle){
	return true;
}

const bool SQLiteDriver::hasConnPolling(){
	return false;
}

void SQLiteDriver::resetConnection(void *conn_handle){
	throw SQL::DriverOperationNotSupported("resetConnection");
}
