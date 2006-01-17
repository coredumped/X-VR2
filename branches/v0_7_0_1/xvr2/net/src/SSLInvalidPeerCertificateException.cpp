/*
 * $Id$
 */
#include<xvr2/SSLInvalidPeerCertificateException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_SSLInvalidPeerCertificate = "xvr2::Exception::SSLInvalidPeerCertificate";
#endif
		static const char *_desc_SSLInvalidPeerCertificate = "Peer's certificate is not valid";

		SSLInvalidPeerCertificate::SSLInvalidPeerCertificate(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_SSLInvalidPeerCertificate);
#endif
			description = (char *)_desc_SSLInvalidPeerCertificate;
		}
	};
};

