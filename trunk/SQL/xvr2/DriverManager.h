/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_DB_DRIVER_MANAGER_H__
#define __XVR2_DB_DRIVER_MANAGER_H__
#include<xvr2/xvr2config.h>
#include<xvr2/String.h>
#include<xvr2/SQL/Driver.h>
#include<xvr2/DSO.h>

namespace xvr2 {
	namespace SQL {

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
