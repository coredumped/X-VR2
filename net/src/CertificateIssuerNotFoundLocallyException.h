/*
 * $Id$
 */
#ifndef __XVR2_NET_CertificateIssuerNotFoundLocally_EXCEPTION_H__
#define __XVR2_NET_CertificateIssuerNotFoundLocally_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/NetworkException.h>
#include<xvr2/X509Exception.h>
namespace xvr2 {
	namespace Exception{

		class CertificateIssuerNotFoundLocally:public X509{
			public:
				/** Default constructor */
				CertificateIssuerNotFoundLocally();
		};

	};
};
#endif

