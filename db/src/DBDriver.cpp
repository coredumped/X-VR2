/*
 * $Id$
 */
#include<DBDriver.h>
#ifdef USE_DEBUG
#include<Console.h>
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
				ret = __drv_connect(((String *)&server)->toCharPtr(), ((String *)&__dbname)->toCharPtr(), ((String *)&user)->toCharPtr(), ((String *)&pass)->toCharPtr(), port);
			}
			catch(...){
				throw;
			}
			return ret;
		}
	
		ResultSet *Driver::query(void *__handle, const String &cmd){
			ResultSet *r = 0;
			try{
				r = __drv_query(__handle, ((String *)&cmd)->toCharPtr());
			}
			catch(...){
				throw;
			}
			if((((String *)&cmd)->startsIWith("update") || ((String *)&cmd)->startsIWith("delete")) && __do_auto_commit){
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
	};
};
