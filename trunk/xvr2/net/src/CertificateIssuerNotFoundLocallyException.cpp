/*
 * $Id$
 */
#include<xvr2/CertificateIssuerNotFoundLocallyException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_CertificateIssuerNotFoundLocally = "xvr2::Exception::CertificateIssuerNotFoundLocally";
#endif
		static const char *_desc_CertificateIssuerNotFoundLocally = "CertificateIssuerNotFoundLocally exception thrown";

		CertificateIssuerNotFoundLocally::CertificateIssuerNotFoundLocally(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_CertificateIssuerNotFoundLocally);
#endif
			description = (char *)_desc_CertificateIssuerNotFoundLocally;
		}
	};
};

