/*
 * $Id$
 */
#include<xvr2/CertificateLoadLocationsException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_CertificateLoadLocations = "xvr2::Exception::CertificateLoadLocations";
#endif
		static const char *_desc_CertificateLoadLocations = "CertificateLoadLocations exception thrown";

		CertificateLoadLocations::CertificateLoadLocations(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_CertificateLoadLocations);
#endif
			description = (char *)_desc_CertificateLoadLocations;
		}
	};
};

