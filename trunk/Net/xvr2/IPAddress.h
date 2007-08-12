/*
 * $Id$
 */
#ifndef __XVR2_NET_IP_ADDRESS_H__
#define __XVR2_NET_IP_ADDRESS_H__
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/Net/NetworkExceptions.h>
#ifdef UNIX_SOCKETS
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#endif

namespace xvr2 {
	namespace Net {

		class IPAddress:public Object {
			protected:
			public:
				IPAddress();
				virtual ~IPAddress();
		};
	};
};

#endif

