/*
 * $Id$
 */
#include<xvr2/X509UnableToDecryptCertificateException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_X509UnableToDecryptCertificate = "xvr2::Exception::X509UnableToDecryptCertificate";
#endif
		static const char *_desc_X509UnableToDecryptCertificate = "X509UnableToDecryptCertificate exception thrown";

		X509UnableToDecryptCertificate::X509UnableToDecryptCertificate(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_X509UnableToDecryptCertificate);
#endif
			description = (char *)_desc_X509UnableToDecryptCertificate;
		}
	};
};

