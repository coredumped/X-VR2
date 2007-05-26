/*
 * $Id$
 */
#ifndef __XVR2_NET_IPV4_ADDRESS_H__
#define __XVR2_NET_IPV4_ADDRESS_H__
#include<iostream>
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/Net/NetworkExceptions.h>
#include<xvr2/Net/IPv4Resolver.h>
#ifdef UNIX_SOCKETS
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#endif

namespace xvr2 {
namespace Net {
	class IPv4Resolver;

	/** \class IPv4Address IPv4Address.h <xvr2/Net/IPv4Address.h>
	 * This class represents a classic IPv4 address, there are several
	 * ways to build an ipv4 address from a String or even by each one
	 * of its octets */
	class IPv4Address:public Object {
		protected:
			/** Internal OS dependent internet space address 
			 *  representation */
			struct ::in_addr addr;
		public:
			/** Default constructor, use it when you'll be needing
			 *  a variable for copying the contents of another IPv4Address
			 *  object. */
			IPv4Address();
			/** Constructs an IPv4Address instance given by a 
			 *  string representation of an ip v4 formatted address or a
			 *  DNS resolvable hostname.
			 *
			 *  During its construction this class will build its internal
			 *  OS-dependent representation by issuing a DNS query in order
			 *  to obtain a valid IP version 4 formatted address for the 
			 *  given argument. 
			 *  \param ip_or_host IP address or hostname from where we will
			 *  be building the address. */
			IPv4Address(const String &ip_or_host);
			/** Builds an IPv4Address object from its 4 octets a.b.c.d */
			IPv4Address(UInt8 a, UInt8 b, UInt8 c, UInt8 d);
			IPv4Address(const IPv4Address &ip);
			IPv4Address(const struct ::in_addr *x_addr);
			IPv4Address(const struct ::in_addr &x_addr);
			~IPv4Address();
			IPv4Address &operator=(const struct ::in_addr *_addr);
			IPv4Address &operator=(const struct ::in_addr &_addr);
			const struct ::in_addr *address() const;
			std::string toString();
			friend std::ostream& operator<<(std::ostream& stream, const IPv4Address &s);
	};
};
};
#endif
