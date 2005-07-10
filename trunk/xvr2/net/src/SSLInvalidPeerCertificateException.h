/*
 * $Id$
 */
#ifndef __XVR2_NET_SSLInvalidPeerCertificate_EXCEPTION_H__
#define __XVR2_NET_SSLInvalidPeerCertificate_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>
#include<xvr2/SSLGenericException.h>
namespace xvr2 {
	namespace Exception{

		class SSLInvalidPeerCertificate:public SSLGeneric{
			public:
				/** Default constructor */
				SSLInvalidPeerCertificate();
		};

	};
};
#endif

