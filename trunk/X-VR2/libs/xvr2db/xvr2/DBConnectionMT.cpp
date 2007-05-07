/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/_xvr2dbClassNames.h>
#include<xvr2/DBConnectionMT.h>

namespace xvr2{

	//Start implementation of class: Connection

	namespace DB {

#ifdef USE_EMBEDDED_CLASSNAMES
		_xvr2ConnectionMT = "ConnectionMT";
#endif

		ConnectionMT::ConnectionMT():Connection(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(_xvr2ConnectionMT);
#endif
		}
	
		ConnectionMT::ConnectionMT(Driver *d):Connection(d){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(_xvr2ConnectionMT);
#endif
		}
	
		ConnectionMT::ConnectionMT(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port):Connection(d, s, dbname, u, p, port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(_xvr2ConnectionMT);
#endif
		}
	
		ConnectionMT::~ConnectionMT(){
			if(isConnected())
				disconnect();
			if(bulk_delim != 0)
				xvr2_delete(bulk_delim);
		}
	
		void ConnectionMT::connect(const String &s, const String &dbname, const String &u, const String &p, int port){
			if(driver->conn_requires_lock) mt.lock();
			try{
				Connection::connect(s, dbname, u, p, port);
			}
			catch(...){
				if(driver->conn_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock) mt.unlock();
		}
	
		void ConnectionMT::connect(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
			if(driver->conn_requires_lock) mt.lock();
			try{
				Connection::connect(d, s, dbname, u, p, port);
			}
			catch(...){
				if(driver->conn_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock) mt.unlock();
		}
	
		void ConnectionMT::connect(){
			if(driver->conn_requires_lock) mt.lock();
			try{
				Connection::connect();
			}
			catch(...){
				if(driver->conn_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock) mt.unlock();
		}
	
		void ConnectionMT::disconnect(){
			if(driver->conn_requires_lock) mt.lock();
			try{
				Connection::disconnect();
			}
			catch(...){
				if(driver->conn_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock) mt.unlock();
		}
	
		ResultSet *ConnectionMT::query(const String &cmd){
			ResultSet *r = 0;
			if(driver->query_requires_lock) mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, cmd.toCharPtr(), __LINE__ + 1, __FILE__);
#endif
#endif
				r = Connection::query(cmd);
			}
			catch(...){
				if(driver->query_requires_lock) mt.unlock();
				throw;
			}
			if(driver->query_requires_lock) mt.unlock();
			return r;
		}

		ResultSet *ConnectionMT::query(const StringBuffer &cmd){
			ResultSet *r = 0;
			if(driver->query_requires_lock) mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, cmd.toCharPtr(), __LINE__ + 1, __FILE__);
#endif
#endif
				r = Connection::query(cmd.toString());
			}
			catch(...){
				if(driver->query_requires_lock) mt.unlock();
				throw;
			}
			if(driver->query_requires_lock) mt.unlock();
			return r;
		}
	
		void ConnectionMT::commit(){
			if(driver->query_requires_lock) mt.lock();
			try{
				Connection::commit();
			}
			catch(...){
				if(driver->query_requires_lock) mt.unlock();
				throw;
			}
			if(driver->query_requires_lock) mt.unlock();
		}
	
		void ConnectionMT::bulkUploadBegin(const String &table, const String &cols, const String &_delim){
			if(driver->conn_requires_lock || driver->query_requires_lock) mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, "BulkUploadBegin", __LINE__ + 1, __FILE__);
#endif
#endif
				Connection::bulkUploadBegin(table, cols, _delim);
			}
			catch(...){
				if(driver->conn_requires_lock || driver->query_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock || driver->query_requires_lock) mt.unlock();
		}

		void ConnectionMT::bulkUploadData(const String &data){
			if(driver->conn_requires_lock || driver->query_requires_lock) mt.lock();
			try{
				Connection::bulkUploadData(data);
			}
			catch(...){
				if(driver->conn_requires_lock || driver->query_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock || driver->query_requires_lock) mt.unlock();
		}

		void ConnectionMT::bulkUploadEnd(){
			if(driver->conn_requires_lock || driver->query_requires_lock) mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, "BulkUploadEnd", __LINE__ + 1, __FILE__);
#endif
#endif
				Connection::bulkUploadEnd();
			}
			catch(...){
				if(driver->conn_requires_lock || driver->query_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock || driver->query_requires_lock) mt.unlock();
		}

		String ConnectionMT::escapeString(const String &str){
			String ret;
			mt.lock();
			try{
				ret = Connection::escapeString(str);
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
			return ret;
		}

		char *ConnectionMT::escapeString(const char *str){
			char *ret = 0;
			//mt.lock();
			try{
				ret = Connection::escapeString(str);
			}
			catch(...){
				//mt.unlock();
				throw;
			}
			//mt.unlock();
			return ret;
		}

		const char *ConnectionMT::errorMessage(){
			char *ret;
			mt.lock();
			try{
				ret = (char *)Connection::errorMessage();
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
			return ret;
		}

		const bool ConnectionMT::isConnected(){
			bool ret;
			if(driver->conn_requires_lock) mt.lock();
			try{
				ret = Connection::isConnected();
			}
			catch(...){
				if(driver->conn_requires_lock) mt.unlock();
				throw;
			}
			if(driver->conn_requires_lock) mt.unlock();
			return ret;
		}

		int ConnectionMT::execCommand(const String &cmd){
			int ret = 0;
			if(driver->query_requires_lock) mt.lock();
			try{
				ret = Connection::execCommand(cmd);
			}
			catch(...){
				if(driver->conn_requires_lock) mt.unlock();
				throw;
			}
			if(driver->query_requires_lock) mt.unlock();
			return ret;
		}

		int ConnectionMT::execCommand(const StringBuffer &cmd){
			int ret = 0;
			if(driver->query_requires_lock) mt.lock();
			try{
				ret = Connection::execCommand(cmd);
			}
			catch(...){
				if(driver->conn_requires_lock) mt.unlock();
				throw;
			}
			if(driver->query_requires_lock) mt.unlock();
			return ret;
		}

	//End implementation of class: ConnectionMT
	};
};

