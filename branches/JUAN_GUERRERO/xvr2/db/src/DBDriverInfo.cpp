/*
 * This class holds information on database driver devices
 *
 * $Id$
 */
#include<DBDriverInfo.h>
#include<MessageStrings.h>

namespace xvr2{
	namespace DB {

		// Start definition of local variables
		// End definition of local variables
	
		// Start definition of local functions
		// End definition of local functions
	
	
	
	
		//Start implementation of class: DriverInfo
	
		DriverInfo::DriverInfo(){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2DBDriverInfo);
#endif
			__version = 0;
			__revision = 0;
			__vendor = constNOVENDOR;
		}
	
		DriverInfo::DriverInfo(int ver, int rev, const String &vend){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2DBDriverInfo);
#endif
			__version = ver;
			__revision = rev;
			__vendor = ((String *)&vend)->toCharPtr();
		}
	
		DriverInfo::DriverInfo(int ver, int rev, const String &vend, const String &desc){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2DBDriverInfo);
#endif
			__version = ver;
			__revision = rev;
			__vendor = ((String *)&vend)->toCharPtr();
			__description = ((String *)&desc)->toCharPtr();
		}
	
		DriverInfo::~DriverInfo(){
		}
	
		const int DriverInfo::version(){
			return (const int)__version;
		}
	
		const int DriverInfo::revision(){
			return (const int)__revision;
		}
	
		const String &DriverInfo::vendor(){
			return __vendor;
		}
	
		const String &DriverInfo::description(){
			return __description;
		}
		//End implementation of class: DriverInfo
	};
};
