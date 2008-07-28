/*
 * This class encapsulates the Driver class and provides a much more complete interface to the SQL database connection paradigm
 *
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/_xvr2dbClassNames.h>
#include<xvr2/DBConnection.h>
#include<xvr2/DatabaseException.h>

namespace xvr2{

	//Start implementation of class: Connection

	namespace DB {


		Connection::Connection(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::_xvr2Connection);
#endif
			driver = 0;
			bulk_delim = 0;
			__conn = 0;
			_server.deleteString();
			__connected = false;	
		}
	
		Connection::Connection(Driver *d){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(xvr2::_xvr2Connection);
#endif
			driver = d;
			bulk_delim = 0;
			__conn = 0;
			_server.deleteString();
			__connected = false;	
		}
	
		Connection::Connection(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
#ifdef USE_EMBEDDED_CLASSNAMES
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
	
		void Connection::connect(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
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
	
		void Connection::connect(){
			if(_server.size() == 0)
				throw DatabaseException();
			try{
				connect(_server, _dbname, _user, _password, _port);
			}
			catch(...){
				throw;
			}
		}
	
		void Connection::disconnect(){
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
	
		ResultSet *Connection::query(const String &cmd){
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

		ResultSet *Connection::query(const StringBuffer &cmd){
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

		int Connection::execCommand(const String &cmd){
			int ret;
			if(!isConnected()){
				throw DBConnectFirst();
			}
			ret = driver->execCommand(__conn, cmd);
			return ret;
		}

		int Connection::execCommand(const StringBuffer &cmd){
			int ret;
			if(!isConnected()){
				throw DBConnectFirst();
			}
			ret = driver->execCommand(__conn, cmd.toString());
			return ret;
		}
	
		void Connection::commit(){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				driver->commit(__conn);
			}
			catch(...){
				throw;
			}
		}
	
		void Connection::bulkUploadBegin(const String &table, const String &cols, const String &_delim){
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

		void Connection::bulkUploadData(const String &data){
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

		void Connection::bulkUploadEnd(){
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
		
		void Connection::bulkDownloadBegin(const String &table, const String &cols, const String &_delim){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				if(bulk_delim != 0)
					xvr2_delete(bulk_delim);
				bulk_delim = new String(_delim.toCharPtr());
				if(!driver->bulkDownloadBegin(__conn, table.toCharPtr(), cols.toCharPtr(), bulk_delim->toCharPtr()))
					throw BulkDownloadStart(table, cols, errorMessage());
			}
			catch(...){
				throw;
			}
		}
		
		xvr2::String Connection::bulkDownloadData(){
			xvr2::String data;
			if(!isConnected())
				throw DBConnectFirst();
			driver->bulkDownloadData(__conn, data);
			return xvr2::String(data);
		}
		
		void Connection::bulkDownloadEnd(){
			if(!isConnected())
				throw DBConnectFirst();
			try{
				if(!driver->bulkDownloadEnd(__conn))
					throw BulkUploadFailed();
			}
			catch(...){
				throw;
			}
		}

		String Connection::escapeString(const String &str){
			return String(driver->escapeString(str, __conn));
		}

		/*char *Connection::escapeString(const char *str){
			return driver->escapeString(str, __conn);
		}*/

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
		
		void Connection::reset(){
			driver->resetConnection(__conn);
		}

	//End implementation of class: Connection
	};
};
