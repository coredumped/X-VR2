/*
 * $Id$
 */
#ifndef __XVR2_NET_SSLConnectFailed_EXCEPTION_H__
#define __XVR2_NET_SSLConnectFailed_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>
#include<xvr2/NetworkException.h>
namespace xvr2 {
	namespace Exception{

		class SSLConnectFailed:public Network{
			public:
				/** Default constructor */
				SSLConnectFailed();
		};

	};
};
#endif

