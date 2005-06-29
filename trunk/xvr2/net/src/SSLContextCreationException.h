/*
 * $Id$
 */
#ifndef __XVR2_NET_SSLContextCreation_EXCEPTION_H__
#define __XVR2_NET_SSLContextCreation_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>
#include<xvr2/NetworkException.h>
namespace xvr2 {
	namespace Exception{

		/** Exception thrown whenever an SSLContext object failed instatiation */
		class SSLContextCreation:public Network{
			public:
				/** Default constructor */
				SSLContextCreation();
		};

	};
};
#endif

