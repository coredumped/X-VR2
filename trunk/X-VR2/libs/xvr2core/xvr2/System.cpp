/*
 * $Id$
 */
#include"config.h"
#include "System.h"
#include<unistd.h>
#ifdef USING_LINUX
#include "SharedVar.h"
#include<cstdio>
#include<Memory.h>
#include "String.h"
#endif

namespace xvr2{

#ifdef USING_LINUX
/*	SharedVar<bool> __lnx_data_gathered(false);
	SharedVar<double> __lnx_cpuSpeed(0.0);
	SharedVar<int> __lnx_installedCPUs(0);
	
	void __lnx_getCPUData(){
		double speed;
		int installedCPUs = 0, ok;
		char *buffer;
		FILE *f = 0;
		String tester;
		if(!__lnx_data_gathered.getValue()){
			buffer = new char[4096];
			f = fopen("/proc/cpuinfo", "r");
			if(f == 0){
				throw FileNotFound();
			}
			while(true){
				Memory::clearBuffer(buffer, 4096);
				if(fgets(buffer, 4094, f) == 0)
					break;
				tester.deleteString();
				tester = buffer;
				if(tester.startsWith("cpu MHz")){
					ok = sscanf((const char *)(buffer + tester.index(":") + 1), "%lf", &speed);
					if(ok != 1){
						throw NumberException();
					}
				}
				else{
					if(tester.startsWith("processor")){
						installedCPUs++;
					}
				}
			}
			__lnx_cpuSpeed.setValue(speed);
			__lnx_installedCPUs.setValue(installedCPUs);
			__lnx_data_gathered.setValue(true);
			//xvr2_delete(f);
			xvr2_delete_array(buffer);
			fclose(f);
		}
	}*/
#endif
	

	System::System(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2System);
#endif
	}

/*	int System::installedCPUs(){
		int num = 0;
#ifdef USING_LINUX
		__lnx_getCPUData();
		num = __lnx_installedCPUs.getValue();
#endif
		return num;
	}

	double System::cpuSpeed(){
		double speed = 0;
#ifdef USING_LINUX
		__lnx_getCPUData();
		speed = __lnx_cpuSpeed.getValue();
#endif
		return speed;
	}

	int System::totalMemory(){
		return (sysconf(_SC_PHYS_PAGES) / 1024) * sysconf(_SC_PAGE_SIZE);
	}

	int System::freeMemory(){
		return (sysconf(_SC_AVPHYS_PAGES) / 1024) * sysconf(_SC_PAGE_SIZE);
	}*/

	void System::usleep(UInt32 usec){
		::usleep(usec);
	}
}
