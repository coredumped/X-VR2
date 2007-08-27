/*
 * $Id:X509Subject.h 535 2007-08-12 10:49:40Z mindstorm2600 $
 */
#ifndef  __XVR2_SSL_X509_SUBJECT_H__
#define  __XVR2_SSL_X509_SUBJECT_H__
#include<xvr2/Net/X509Name.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2 {
namespace Net {
	class X509Subject:public X509Name {
		public:
			X509Subject(const String &x509_name);
	};
};
};

#endif
