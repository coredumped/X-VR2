/*
 * $Id$
 */
#include<xvr2/CertificateIssuerNotFoundLocallyException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_CertificateIssuerNotFoundLocally = "xvr2::Exception::CertificateIssuerNotFoundLocally";
#endif
		static const char *_desc_CertificateIssuerNotFoundLocally = "CertificateIssuerNotFoundLocally exception thrown";

		CertificateIssuerNotFoundLocally::CertificateIssuerNotFoundLocally(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_CertificateIssuerNotFoundLocally);
#endif
			description = (char *)_desc_CertificateIssuerNotFoundLocally;
		}
	};
};

