/*
 * $Id$
 */
#include<xvr2/X509IssuerCertificateNotFoundException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_X509IssuerCertificateNotFound = "xvr2::Exception::X509IssuerCertificateNotFound";
#endif
		static const char *_desc_X509IssuerCertificateNotFound = "X509IssuerCertificateNotFound exception thrown";

		X509IssuerCertificateNotFound::X509IssuerCertificateNotFound(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_X509IssuerCertificateNotFound);
#endif
			description = (char *)_desc_X509IssuerCertificateNotFound;
		}
	};
};

