/*
 * $Id$
 */
#ifndef __XVR2_SYSTEM_H__
#define __XVR2_SYSTEM_H__
#include<xvr2/Object.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	/**
	 * This class is an interface for all System classes
	 */
	class System:public Object{
		public:
			/** Default Constructor, remember that this class
			 * is just an interface */
			System();
			/** This will return how many CPUs are installed in the system */
			//static int installedCPUs();
			/** This will return the CPU speed in megahertz */
			//static double cpuSpeed();
			/** Will return the total amount of system memory */
			//static int totalMemory();
			/** Will return the total amount of free system memory */
			//static int freeMemory();
			/** Will freeze the software for <b>usec</b> microseconds */
			static void usleep(UInt32 usec);
	};
}

#endif
