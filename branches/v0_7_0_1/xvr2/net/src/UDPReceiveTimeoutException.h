/*
 * $Id$
 */
#ifndef __XVR2_NET_UDPReceiveTimeout_EXCEPTION_H__
#define __XVR2_NET_UDPReceiveTimeout_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/NetworkException.h>
#include<xvr2/NetworkException.h>
namespace xvr2 {
	namespace Exception{

		class UDPReceiveTimeout:public Network{
			public:
				/** Default constructor */
				UDPReceiveTimeout();
		};

	};
};
#endif

