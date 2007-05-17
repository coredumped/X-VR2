/*
 * $Id$
 */
#include<xvr2/CertificateLookupPendingException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_CertificateLookupPending = "xvr2::Exception::CertificateLookupPending";
#endif
		static const char *_desc_CertificateLookupPending = "CertificateLookupPending exception thrown";

		CertificateLookupPending::CertificateLookupPending(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_CertificateLookupPending);
#endif
			description = (char *)_desc_CertificateLookupPending;
		}
	};
};

