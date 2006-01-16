/*
 * $Id$
 */
#include<xvr2/CertificateIssuerNotFoundLocallyException.h>

namespace xvr2 {
	namespace Exception{
#if GCC_MAJOR_VERSION < 3
		static const char *_local_class_name_CertificateIssuerNotFoundLocally = "xvr2::Exception::CertificateIssuerNotFoundLocally";
#endif
		static const char *_desc_CertificateIssuerNotFoundLocally = "CertificateIssuerNotFoundLocally exception thrown";

		CertificateIssuerNotFoundLocally::CertificateIssuerNotFoundLocally(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)_local_class_name_CertificateIssuerNotFoundLocally);
#endif
			description = (char *)_desc_CertificateIssuerNotFoundLocally;
		}
	};
};

