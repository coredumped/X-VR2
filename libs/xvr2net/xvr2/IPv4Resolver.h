/*
 * $Id$
 */
#ifndef __XVR2_NET_IPV4_RESOLVER_H__
#define __XVR2_NET_IPV4_RESOLVER_H__
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<xvr2/Object.h>
#include<xvr2/System.h>
#include<xvr2/IPv4Address.h>
#include<xvr2/NetworkExceptions.h>

namespace xvr2 {
namespace Net {
	class IPv4Address;
	class IPv4Resolver:public xvr2::System {
		public:
			static IPv4Address *resolve(const String &ip_or_host);
			//static String *reverse_lookup(const String &ip_address);
	};
};
};

#endif
