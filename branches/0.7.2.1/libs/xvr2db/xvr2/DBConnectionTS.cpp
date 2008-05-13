/*
 * This class encapsulates the Driver class and provides a much more complete interface to the SQL database connection paradigm
 *
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/_xvr2dbClassNames.h>
#include<xvr2/DBConnectionTS.h>
#include<xvr2/DatabaseException.h>

namespace xvr2{

	//Start implementation of class: ConnectionTS

	namespace DB {


		ConnectionTS::ConnectionTS(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::_xvr2ConnectionTS);
#endif
			driver = 0;
			bulk_delim = 0;
			__conn = 0;
			_server.deleteString();
			__connected = false;	
		}
	
		ConnectionTS::ConnectionTS(Driver *d){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::_xvr2ConnectionTS);
#endif
			driver = d;
			bulk_delim = 0;
			__conn = 0;
			_server.deleteString();
			__connected = false;	
		}
	
		ConnectionTS::ConnectionTS(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::_xvr2ConnectionTS);
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
	
		ConnectionTS::~ConnectionTS(){
			if(isConnected())
				disconnect();
			if(bulk_delim != 0)
				xvr2_delete(bulk_delim);
		}
	
		void ConnectionTS::connect(const String &s, const String &dbname, const String &u, const String &p, int port){
			if(isConnected())
				throw AlreadyConnected2DB();
			if(bulk_delim != 0)
				xvr2_delete(bulk_delim);
			try{
				__conn = driver->connect(s, dbname, u, p, port);
			}
			catch(...){
				throw;
			}
	
			if(__conn == 0){
				throw DatabaseException();
			}
			__connected = true;
		}
	
		void ConnectionTS::connect(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
			if(driver == 0){
				bulk_delim = 0;
				__conn = 0;
				_server.deleteString();
				__connected = false;	
			}
			driver = d;
			if(isConnected())
				throw AlreadyConnected2DB();
			if(bulk_delim != 0)
				xvr2_delete(bulk_delim);
			try{
				__conn = driver->connect(s, dbname, u, p, port);
			}
			catch(...){
				throw;
			}
	
			if(__conn == 0){
				throw DatabaseException();
			}
			__connected = true;
		}
	
		void ConnectionTS::connect(){
			if(_server.size() == 0)
				throw DatabaseException();
			try{
				connect(_server, _dbname, _user, _password, _port);
			}
			catch(...){
				throw;
			}
		}
	
		void ConnectionTS::disconnect(){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				driver->disconnect(__conn);
			}
			catch(...){
				throw;
			}
			__conn = 0;
			__connected = false;
		}
	
		ResultSet *ConnectionTS::query(const String &cmd){
			ResultSet *r = 0;
			if(!isConnected())
				throw DBConnectFirst();
			try{
				r = driver->query(__conn, cmd);
			}
			catch(...){
				throw;
			}
			if(r == 0){
				throw DatabaseException();
			}
			return r;
		}

		ResultSet *ConnectionTS::query(const StringBuffer &cmd){
			ResultSet *r = 0;
			if(!isConnected())
				throw DBConnectFirst();
			try{
				r = driver->query(__conn, cmd.toString());
			}
			catch(...){
				throw;
			}
			if(r == 0){
				throw DatabaseException();
			}
			return r;
		}

		int ConnectionTS::execCommand(const String &cmd){
			int ret;
			if(!isConnected()){
				throw DBConnectFirst();
			}
			ret = driver->execCommand(__conn, cmd);
			return ret;
		}

		int ConnectionTS::execCommand(const StringBuffer &cmd){
			int ret;
			if(!isConnected()){
				throw DBConnectFirst();
			}
			ret = driver->execCommand(__conn, cmd.toString());
			return ret;
		}
	
		void ConnectionTS::commit(){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				driver->commit(__conn);
			}
			catch(...){
				throw;
			}
		}
	
		void ConnectionTS::bulkUploadBegin(const String &table, const String &cols, const String &_delim){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				if(bulk_delim != 0)
					xvr2_delete(bulk_delim);
				bulk_delim = new String(_delim.toCharPtr());
				if(!driver->bulkBegin(__conn, table.toCharPtr(), cols.toCharPtr(), bulk_delim->toCharPtr()))
					throw BulkUploadStart();
			}
			catch(...){
				throw;
			}
		}

		void ConnectionTS::bulkUploadData(const String &data){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				if(!driver->bulkAddData(__conn, data.toCharPtr(), bulk_delim->toCharPtr()))
					throw BulkDataParse();
			}
			catch(...){
				throw;
			}
		}

		void ConnectionTS::bulkUploadEnd(){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				if(!driver->bulkEnd(__conn))
					throw BulkUploadFailed();
			}
			catch(...){
				throw;
			}
		}

		String ConnectionTS::escapeString(const String &str){
			return driver->escapeString(str, __conn);
		}

		char *ConnectionTS::escapeString(const char *str){
			return driver->quoteString(str);
		}

		const char *ConnectionTS::errorMessage(){
			return driver->errorMessage(__conn);
		}

		const bool ConnectionTS::isConnected(){
			if(__conn == 0){
				__connected = false;
			}
			else if(driver->hasConnPolling()){
				__connected = driver->isConnected(__conn);
			}
			return __connected;
		}
		
		void ConnectionTS::lock(){
			dbcm.lock();
		}
		
		void ConnectionTS::unlock(){
			dbcm.unlock();
		}

	//End implementation of class: ConnectionTS
	};
};
