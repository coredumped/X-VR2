/*
 * $Id$
 */
#ifndef __XVR2_NET_X509_EXCEPTION_H__
#define __XVR2_NET_X509_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/NetworkException.h>
#include<xvr2/CryptoException.h>
namespace xvr2 {
	namespace Exception{

		class X509:public Crypto{
			public:
				/** Default constructor */
				X509();
		};

	};
};
#endif

