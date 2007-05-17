/*
 * $Id$
 */
#ifndef __XVR2_NET_IPV4_ADDRESS_H__
#define __XVR2_NET_IPV4_ADDRESS_H__
#include<sys/socket.h>
#include<iostream>
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/Net/NetworkExceptions.h>
#include<xvr2/Net/IPv4Resolver.h>
#ifdef UNIX_SOCKETS
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#endif

namespace xvr2 {
namespace Net {
	class IPv4Resolver;
	class IPv4Address:public Object {
		protected:
			struct ::sockaddr_in addr;
		public:
			IPv4Address(const String &ip_or_host);
			IPv4Address(UInt8 a, UInt8 b, UInt8 c, UInt8 d);
			IPv4Address(const IPv4Address &ip);
			IPv4Address(const struct ::sockaddr_in *x_addr);
			~IPv4Address();
			const struct ::sockaddr_in *sockAddr() const;
			//   /* Will return a String representation of the IP address, you
			//    * must explicitely release the allocated memory after use. */
			//String *toString();
			std::string toString();
			friend std::ostream& operator<<(std::ostream& stream, const IPv4Address &s);
	};
};
};
#endif
