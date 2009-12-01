/*
 * $Id:DriverInfo.h 540 2007-08-20 07:51:56Z mindstorm2600 $
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
#include<xvr2/xvr2config.h>
#include<xvr2/Object.h>
#include<xvr2/String.h>

#ifndef __XVR2_SQL_DriverInfo_H__
#define __XVR2_SQL_DriverInfo_H__

namespace xvr2{
	namespace SQL {
		/**
		 * This class holds information on database driver devices
		 */
		class DriverInfo:public Object{
			private:
			protected:
				/** Holds the driver's version */
				int __version;
				/** Holds the driver's reversion */
				int __revision;
				/** Holds the driver's vendor/author */
				String __vendor;
				/** Holds the driver's description */
				String __description;
			public:
				/** Default constructor */
				DriverInfo();
				/** This constructor will initialize the 
				 *  values for
				 *  version, revision and vendor */
				DriverInfo(int ver, int rev, const String &vend);
				/** This constructor will initialize the 
				 *  values for version, revision, vendor 
				 *  and description */
				DriverInfo(int ver, int rev, const String &vend, const String &desc);
				/** The destructor, currently this 
				 *  destructor does not perform any 
				 *  function */
				~DriverInfo();
				/** This will return the version of the 
				 *  driver */
				const int version();
				/** This will return the revision of the 
				 *  driver */
				const int revision();
				/** This will return the vendor or the 
				 *  author of the driver */
				const String &vendor();
				/** This will return the driver description 
				 *  string */
				const String &description();
		};
	};
};

#endif
