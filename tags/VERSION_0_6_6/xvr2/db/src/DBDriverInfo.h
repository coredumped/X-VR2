/*
 * $Id$
 */

#include<Object.h>
#include<String.h>

#ifndef __XVR2_DB_DriverInfo_H__
#define __XVR2_DB_DriverInfo_H__

namespace xvr2{
	namespace DB {
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
