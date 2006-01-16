/*
 * $Id$
 */
#include<xvr2/CertificateLoadLocationsException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_CertificateLoadLocations = "xvr2::Exception::CertificateLoadLocations";
#endif
		static const char *_desc_CertificateLoadLocations = "CertificateLoadLocations exception thrown";

		CertificateLoadLocations::CertificateLoadLocations(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_CertificateLoadLocations);
#endif
			description = (char *)_desc_CertificateLoadLocations;
		}
	};
};

