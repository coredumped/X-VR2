/*
 * $Id$
 */
#include<xvr2/DBDriverManager.h>

namespace xvr2 {
	namespace DB {
		
		DriverManager::DriverManager(const String &dsopath){
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
		}
	};
};
