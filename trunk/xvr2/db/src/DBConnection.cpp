/*
 * This class encapsulates the Driver class and provides a much more complete interface to the SQL database connection paradigm
 *
 * $Id$
 */
#include<xvr2/DBConnection.h>
#include<xvr2/DatabaseException.h>

namespace xvr2{

	//Start implementation of class: Connection

	namespace DB {


		Connection::Connection(){
#if GCC_MAJOR_VERSION < 3
			setClassName(xvr2::_xvr2Connection);
#endif
			driver = 0;
			bulk_delim = 0;
			__conn = 0;
			_server.deleteString();
			__connected = false;	
		}
	
		Connection::Connection(Driver *d){
#if GCC_MAJOR_VERSION < 3
			setClassName(xvr2::_xvr2Connection);
#endif
			driver = d;
			bulk_delim = 0;
			__conn = 0;
			_server.deleteString();
			__connected = false;	
		}
	
		Connection::Connection(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
#if GCC_MAJOR_VERSION < 3
			setClassName(xvr2::_xvr2Connection);
#endif
			driver = d;
			bulk_delim = 0;
			__conn = 0;
			_server.deleteString();
			__connected = false;	
			_server.assign(s);
			_user.assign(u);
			_password.assign(p);
			_dbname.assign(dbname);
			_port = port;
		}
	
		Connection::~Connection(){
			if(isConnected())
				disconnect();
			if(bulk_delim != 0)
				xvr2_delete(bulk_delim);
		}
	
		void Connection::connect(const String &s, const String &dbname, const String &u, const String &p, int port){
			if(isConnected())
				throw Exception::AlreadyConnected2DB();
			if(bulk_delim != 0)
				xvr2_delete(bulk_delim);
			try{
				__conn = driver->connect(s, dbname, u, p, port);
			}
			catch(...){
				throw;
			}
	
			if(__conn == 0){
				throw Exception::Database();
			}
			__connected = true;
		}
	
		void Connection::connect(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
			if(driver == 0){
				bulk_delim = 0;
				__conn = 0;
				_server.deleteString();
				__connected = false;	
			}
			driver = d;
			if(isConnected())
				throw Exception::AlreadyConnected2DB();
			if(bulk_delim != 0)
				xvr2_delete(bulk_delim);
			try{
				__conn = driver->connect(s, dbname, u, p, port);
			}
			catch(...){
				throw;
			}
	
			if(__conn == 0){
				throw Exception::Database();
			}
			__connected = true;
		}
	
		void Connection::connect(){
			if(_server.size() == 0)
				throw Exception::Database();
			try{
				connect(_server, _dbname, _user, _password, _port);
			}
			catch(...){
				throw;
			}
		}
	
		void Connection::disconnect(){
			if(!isConnected())
				throw Exception::DBConnectFirst();
			try{
				driver->disconnect(__conn);
			}
			catch(...){
				throw;
			}
			__conn = 0;
			__connected = false;
		}
	
		ResultSet *Connection::query(const String &cmd){
			ResultSet *r = 0;
			if(!isConnected())
				throw Exception::DBConnectFirst();
			try{
				r = driver->query(__conn, cmd);
			}
			catch(...){
				throw;
			}
			if(r == 0){
				throw Exception::Database();
			}
			return r;
		}
	
		void Connection::commit(){
			if(!isConnected())
				throw Exception::DBConnectFirst();
			try{
				driver->commit(__conn);
			}
			catch(...){
				throw;
			}
		}
	
		void Connection::bulkUploadBegin(const String &table, const String &cols, const String &_delim){
			if(!isConnected())
				throw Exception::DBConnectFirst();
			try{
				if(bulk_delim != 0)
					xvr2_delete(bulk_delim);
				bulk_delim = new String(_delim.toCharPtr());
				if(!driver->bulkBegin(__conn, table.toCharPtr(), cols.toCharPtr(), bulk_delim->toCharPtr()))
					throw Exception::BulkUploadStart();
			}
			catch(...){
				throw;
			}
		}

		void Connection::bulkUploadData(const String &data){
			if(!isConnected())
				throw Exception::DBConnectFirst();
			try{
				if(!driver->bulkAddData(__conn, data.toCharPtr(), bulk_delim->toCharPtr()))
					throw Exception::BulkDataParse();
			}
			catch(...){
				throw;
			}
		}

		void Connection::bulkUploadEnd(){
			if(!isConnected())
				throw Exception::DBConnectFirst();
			try{
				if(!driver->bulkEnd(__conn))
					throw Exception::BulkUploadFailed();
			}
			catch(...){
				throw;
			}
		}

		char *Connection::escapeString(const char *str){
			return driver->quoteString(str);
		}

		const char *Connection::errorMessage(){
			return driver->errorMessage(__conn);
		}

		const bool Connection::isConnected(){
			if(__conn == 0){
				__connected = false;
			}
			else if(driver->hasConnPolling()){
				__connected = driver->isConnected(__conn);
			}
			return __connected;
		}

	//End implementation of class: Connection
	};
};
