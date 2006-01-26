/*
 * $Id$
 */
#ifndef  __XVR2_SSL_X509_SUBJECT_H__
#define  __XVR2_SSL_X509_SUBJECT_H__
#include<xvr2/X509Name.h>
#include<xvr2/NetworkExceptions.h>

namespace xvr2 {
namespace Net {
	class X509Subject:public X509Name {
		public:
			X509Subject(const String &x509_name);
	};
};
};

#endif
