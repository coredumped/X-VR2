/*
 * $Id$
 */
#ifndef  __XVR2_SSL_X509_ISSUER_H__
#define  __XVR2_SSL_X509_ISSUER_H__
#include<xvr2/Net/X509Name.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2 {
namespace Net {
	class X509Issuer:public X509Name {
		public:
			X509Issuer(const String &x509_name);
	};
};
};

#endif
