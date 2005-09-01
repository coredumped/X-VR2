/*
 * $Id$
 */
#include<xvr2/DBDriver.h>
#ifdef USE_DEBUG
#include<xvr2/Console.h>
#endif

namespace xvr2{

	namespace DB {

		Driver::Driver(const String &soname){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2Driver);
#endif
			__is_loaded = false;
			__drv = new Plugin(soname);
			__do_auto_commit = false;
		}
	
		Driver::~Driver(){
			if(__is_loaded)
				__drv_cleanup();
			xvr2_delete(__drv);
		}
	
		void Driver::load(){
#ifdef USE_DEBUG
			std::cerr << "loading driver..." << std::endl;
#endif
			try{
				__drv->load();
			}
			catch(...){
				throw;
			}
#ifdef USE_DEBUG
			std::cerr << "  loading driver symbols..." << std::endl;
#endif
			__drv_cleanup = (bool (*)())__drv->getSymbol("__drv_cleanup");
			__drv_init = (bool (*)(Driver *))__drv->getSymbol("__drv_init");
			__drv_connect = (void *(*)(const char *, const char *, const char *, const char *, int))__drv->getSymbol("__drv_connect");
			__drv_disconnect = (UInt32 (*)(void *))__drv->getSymbol("__drv_disconnect");
			__drv_getVersionInfo = (bool (*)(DB::DriverInfo **))__drv->getSymbol("__drv_getVersionInfo");
			__drv_commit = (bool (*)(void *))__drv->getSymbol("__drv_commit");
			__drv_query = (ResultSet *(*)(void *, const char *))__drv->getSymbol("__drv_query");
	
			//ResultSet drivers
			__drv_fetch_next_row = (Field *(*)(void *))__drv->getSymbol("__drv_fetch_next_row");
			__drv_numcols = (int (*)(void *))__drv->getSymbol("__drv_numcols");
			__drv_numrows = (int (*)(void *))__drv->getSymbol("__drv_numrows");
			__drv_free_resultset = (bool (*)(void *))__drv->getSymbol("__drv_free_resultset");
	
			try{
				__drv_bulk_begin = (bool (*)(void *, const char *, const char *, const char *))__drv->getSymbol("__drv_bulk_begin");
				has__drv_bulk_begin = true;
				__drv_bulk_insert = (bool (*)(void *, const char *, const char *))__drv->getSymbol("__drv_bulk_insert");
				has__drv_bulk_insert = true;
				__drv_bulk_end = (bool (*)(void *))__drv->getSymbol("__drv_bulk_end");
				has__drv_bulk_end = true;
			}
			catch(...){
				__drv_bulk_begin = 0;
				__drv_bulk_insert = 0;
				__drv_bulk_end = 0;
				has__drv_bulk_begin = false;
				has__drv_bulk_insert = false;
				has__drv_bulk_end = false;
#ifdef USE_DEBUG
				std::cerr << "  WARNING: driver is not bulk load capable";
#endif
			}

			try {
				__drv_connected = (bool (*)(void *))__drv->getSymbol("__drv_connected");
				has_conn_polling = true;
			}
			catch(...){
				__drv_connected = 0;
				has_conn_polling = false;
			}

			__drv_quote_string = (char *(*)(const char *))__drv->getSymbol("__drv_quote_string");
			__drv_error_message = (char *(*)(void *))__drv->getSymbol("__drv_error_message");
			__drv_result_error_message = (char *(*)(void *))__drv->getSymbol("__drv_result_error_message");
#ifdef USE_DEBUG
			std::cerr << "  initializing driver...";
#endif
			__drv_init(this);
#ifdef USE_DEBUG
			std::cerr << "done\ndriver loaded" << std::endl;
#endif
			__is_loaded = true;
		}
	
		void Driver::getVersionInfo(DB::DriverInfo **info){
			__drv_getVersionInfo(info);
		}
	
		void *Driver::connect(const String &server, const String &__dbname, const String &user, const String &pass, int port){
			void *ret;
			try{
				ret = __drv_connect(server.toCharPtr(), __dbname.toCharPtr(), user.toCharPtr(), pass.toCharPtr(), port);
			}
			catch(...){
				throw;
			}
			return ret;
		}

		static const char *__upd_str = "update";
		static const char *__del_str = "delete";
	
		ResultSet *Driver::query(void *__handle, const String &cmd){
			ResultSet *r = 0;
			try{
				r = __drv_query(__handle, cmd.toCharPtr());
			}
			catch(...){
				throw;
			}
			if((cmd.startsIWith(__upd_str) || cmd.startsIWith(__del_str)) && __do_auto_commit){
				commit(__handle);
			}
			return r;
		}
	
		bool Driver::disconnect(void *__handle){
			bool ret;
			try{
				ret = __drv_disconnect(__handle);
			}
			catch(...){
				throw;
			}
			return ret;
		}
	
		void Driver::setAutoCommit(bool val){
			__do_auto_commit = val;
		}
	
		void Driver::commit(void *__handle){
			try{
				__drv_commit(__handle);
			}
			catch(...){
				throw;
			}
		}
	
		const int Driver::numRows(void *__res_handle){
			return __drv_numrows(__res_handle);
		}
	
		const int Driver::numCols(void *__res_handle){
			return __drv_numcols(__res_handle);
		}
	
		Field *Driver::fetchRow(void *__res_handle){
			return __drv_fetch_next_row(__res_handle);
		}
	
		const bool Driver::freeResultSet(void *__res_handle){
			return __drv_free_resultset(__res_handle);
		}

		const bool Driver::bulkBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim){
			bool ret;
			if(!has__drv_bulk_begin){
#ifdef USE_DEBUG
				std::cerr << "  WARNING: driver is not bulk load capable";
#endif
				return false;
			}
			try{
				ret = __drv_bulk_begin(conn_handle, tablename, cols, delim);
			}
			catch(...){
				throw;
			}
			return ret;
		}

		const bool Driver::bulkAddData(void *conn_handle, const char *data, const char *delim){
			bool ret;
			if(!has__drv_bulk_insert){
#ifdef USE_DEBUG
				std::cerr << "  WARNING: driver is not bulk load capable";
#endif
				return false;
			}
			try{
				ret = __drv_bulk_insert(conn_handle, data, delim);
			}
			catch(...){
				throw;
			}
			return ret;
		}

		const bool Driver::bulkEnd(void *conn_handle){
			bool ret;
			if(!has__drv_bulk_end){
#ifdef USE_DEBUG
				std::cerr << "  WARNING: driver is not bulk load capable";
#endif
				return false;
			}
			try{
				ret = __drv_bulk_end(conn_handle);
			}
			catch(...){
				throw;
			}
			return ret;
		}

		char *Driver::quoteString(const char *str){
			//char *__drv_quote_string(const char *in);
			return __drv_quote_string(str);
		}

		const char *Driver::errorMessage(void *conn_handle){
			//char *__drv_error_message(void *handle);
			return __drv_error_message(conn_handle);
		}

		const char *Driver::resultErrorMessage(void *res_handle){
			//char *__drv_result_error_message(void *r);
			return __drv_result_error_message(res_handle);
		}

		const bool Driver::isConnected(void *conn_handle){
			if(hasConnPolling()){
				return __drv_connected(conn_handle);
			}
			return false;
		}
	};
};
