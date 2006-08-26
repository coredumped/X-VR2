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
			mt.lock();
			try{
				Connection::connect(s, dbname, u, p, port);
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
		}
	
		void ConnectionMT::connect(Driver *d, const String &s, const String &dbname, const String &u, const String &p, int port){
			mt.lock();
			try{
				Connection::connect(d, s, dbname, u, p, port);
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
		}
	
		void ConnectionMT::connect(){
			mt.lock();
			try{
				Connection::connect();
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
		}
	
		void ConnectionMT::disconnect(){
			mt.lock();
			try{
				Connection::disconnect();
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
		}
	
		ResultSet *ConnectionMT::query(const String &cmd){
			ResultSet *r = 0;
			mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, cmd.toCharPtr(), __LINE__ + 1, __FILE__);
#endif
#endif
				r = Connection::query(cmd);
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
			return r;
		}

		ResultSet *ConnectionMT::query(const StringBuffer &cmd){
			ResultSet *r = 0;
			mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, cmd.toCharPtr(), __LINE__ + 1, __FILE__);
#endif
#endif
				r = Connection::query(cmd.toString());
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
			return r;
		}
	
		void ConnectionMT::commit(){
			mt.lock();
			try{
				Connection::commit();
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
		}
	
		void ConnectionMT::bulkUploadBegin(const String &table, const String &cols, const String &_delim){
			mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, "BulkUploadBegin", __LINE__ + 1, __FILE__);
#endif
#endif
				Connection::bulkUploadBegin(table, cols, _delim);
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
		}

		void ConnectionMT::bulkUploadData(const String &data){
			mt.lock();
			try{
				Connection::bulkUploadData(data);
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
		}

		void ConnectionMT::bulkUploadEnd(){
			mt.lock();
			try{
#ifdef USE_DEBUG
#ifdef DEBUG_SQL
				debugmsgln(this, "BulkUploadEnd", __LINE__ + 1, __FILE__);
#endif
#endif
				Connection::bulkUploadEnd();
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
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
			mt.lock();
			try{
				ret = Connection::isConnected();
			}
			catch(...){
				mt.unlock();
				throw;
			}
			mt.unlock();
			return ret;
		}

	//End implementation of class: ConnectionMT
	};
};
