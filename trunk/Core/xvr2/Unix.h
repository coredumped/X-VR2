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
#ifndef __XVR2_UNIX_H__
#define __XVR2_UNIX_H__
#include<xvr2/System.h>
#include<xvr2/Mutex.h>
#include<xvr2/String.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{

	/** This class implements the most common Unix system calls
	 *  @todo Find a place for the Unix class. */
	class Unix:public System{
		protected:
			/** Pointer to system name */
			char *sysname;
			char *nodename;
			char *release;
			char *k_version;
			char *machine;
			//static Mutex OSMutex;
			Mutex OSMutex;
			/** Internal destructor function 
			 *  <b>DONT USE IT</b> */
			void destroyAll();
		public:
			Unix();
			~Unix();

			/** Obtains the current (running) user id */
			static int getuid();

			/** Obtain uid from username */
			static int getuid(const String &username);

			/** Obtain username from uid
			 TODO: You must create the memory allocation
			 classes if you want to implement the new version
			 of getuid();   DONT FORGET IT!!!!
			*/

			/** Obtains the current (running) user id */
			static int getgid();

			/** Obtain uid from username */
			static int getgid(const String &groupname);

			/** Obtain username from uid
			 TODO: You must create the memory allocation
			 classes if you want to implement the new version
			 of getgid();   DONT FORGET IT!!!!
			*/

			/** Changes the owner of the file by its numeric userid */
			static int chown(const String &fname, int userid, int groupid = -1);
			/** Changes the owner of the file by its username */
			static int chown(const String &fname, const String &owner);
			/** Changes the group owner of the file by its numeric userid */
			static int chgrp(const String &fname, int userid);
			/** Changes the group owner of the file by its groupname */
			static int chgrp(const String &fname, const String &groupname);



			//////////// KERNEL INFO SECTION ////////////


			/** This method will update the name and information about the current running kernel */
			void getKernelInfo();
			/** Use this method to retreives the name of the UNIX version you are currently using */
			const char *getUnixName();
			/** This method will give you the <b>nodename</b> of your current host machine */
			const char *getNodeName();
			/** This will return your current kernel release string */
			const char *getKernelRelease();
			/** This will return your current kernel release version string */
			const char *getKernelReleaseVersion();
			/** This will return your current architecture description */
			const char *getHostMachine();
	};

	//extern Unix *OS;
};

#endif
