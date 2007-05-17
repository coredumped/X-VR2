/*
 * $Id$
 */
#ifndef __XVR2_DB_DRIVER_MANAGER_H__
#define __XVR2_DB_DRIVER_MANAGER_H__
#include<xvr2/xvr2config.h>
#include<xvr2/String.h>
#include<xvr2/DB/Driver.h>
#include<xvr2/DSO.h>

namespace xvr2 {
	namespace DB {

		/**
		 * Use thid class to load and instantiate new drivers to be used. */
		class DriverManager : public Object {
			private:
			protected:
				DSO *dso;
			public:
				DriverManager(const String &dsopath);
				~DriverManager();
				Driver *load();
				//static BasicDriver *load(const String &dsofile);
				static Driver *load(DSO *dso_obj);
				void unload(Driver *drv);
				//static void destroy(BasicDriver *drv, const String &dsofile);
				static void unload(Driver *drv, DSO *dso_obj);
		};
	};
};

#endif
