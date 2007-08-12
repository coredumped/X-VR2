/*
 * $Id:DBDriverManager.cpp 531 2007-08-11 09:05:29Z mindstorm2600 $
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2dbClassNames.h"
#include"DriverManager.h"

namespace xvr2 {
	namespace DB {
		
		DriverManager::DriverManager(const String &dsopath){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_DB_DriverManager);
#endif
			dso = new DSO(dsopath);
		}
	
		DriverManager::~DriverManager(){
			delete dso;
		}
	
		/*BasicDriver *DriverManager::load(const String &dsofile){
			BasicDriver *drv;
			DSO d = new DSO(dsofile);
			d->load();
			drv = load(d);
			delete d;
			return drv;
		}*/
		
		Driver *DriverManager::load(DSO *dso_obj){
			/*PostgreSQLDriver *create_dbdriver_instance();
			void destroy_dbdriver_instance(PostgreSQLDriver *obj);*/
			Driver *drv;
			drv = dso_obj->createObject<Driver>("create_dbdriver_instance");
			return drv;
		}
	
		Driver *DriverManager::load(){
			if(!dso->isLoaded()) dso->load();
			return DriverManager::load(dso);
		}
	
		/*void DriverManager::destroy(BasicDriver *drv, const String &dsofile){
			DSO d = new DSO(dsofile);
			d->load();
			d->destroyObject<BasicDriver>(drv, "destroy_dbdriver_instance");
			delete d;
			return drv;
		}*/
	
		void DriverManager::unload(Driver *drv, DSO *dso_obj){
			dso_obj->destroyObject<Driver>(drv, "destroy_dbdriver_instance");
		}
	
		void DriverManager::unload(Driver *drv){
			DriverManager::unload(drv, dso);
			dso->unload();
		}
	};
};
