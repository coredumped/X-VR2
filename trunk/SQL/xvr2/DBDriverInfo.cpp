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
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/MessageStrings.h>
#include"DriverInfo.h"

namespace xvr2{
	namespace SQL {

		// Start definition of local variables
		// End definition of local variables
	
		// Start definition of local functions
		// End definition of local functions
	
	
	
	
		//Start implementation of class: DriverInfo
	
		DriverInfo::DriverInfo(){
			__version = 0;
			__revision = 0;
			__vendor = constNOVENDOR;
		}
	
		DriverInfo::DriverInfo(int ver, int rev, const String &vend){
			__version = ver;
			__revision = rev;
			__vendor = vend.toCharPtr();
		}
	
		DriverInfo::DriverInfo(int ver, int rev, const String &vend, const String &desc){
			__version = ver;
			__revision = rev;
			__vendor = vend.toCharPtr();
			__description = desc.toCharPtr();
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
