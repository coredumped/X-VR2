/*
 * $Id$
 */
#include<xvr2/SSLInvalidCertificateException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_SSLInvalidCertificate = "xvr2::Exception::SSLInvalidCertificate";
#endif
		static const char *_desc_SSLInvalidCertificate = "Certificate is not valid";

		SSLInvalidCertificate::SSLInvalidCertificate(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_SSLInvalidCertificate);
#endif
			description = (char *)_desc_SSLInvalidCertificate;
		}
	};
};

