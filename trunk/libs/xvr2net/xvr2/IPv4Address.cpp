/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/Memory.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/Util/c_utilities.h>
#include<xvr2/Util/Regex.h>
#include<xvr2/Util/ExtendedRegex.h>
#include"_xvr2netClassNames.h"
#include"IPv4Address.h"
#include<arpa/inet.h>
#include<errno.h>

#ifndef IPV4_ADDRESS_REGEX
#define IPV4_ADDRESS_REGEX "[0-9]+(\\.[0-9]+){3}"
#endif

namespace xvr2 {
	namespace Net {

		IPv4Address::IPv4Address(){
#ifdef USE_EMBEDDED_CLASSNAMESS

			setClassName(__xvr2_Net_IPv4Address);
#endif
			bzero(&addr, sizeof(struct ::in_addr));
		}

		IPv4Address::IPv4Address(const String &ip_or_host){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_IPv4Address);
#endif
			bzero(&addr, sizeof(struct ::in_addr));
			if(inet_aton(ip_or_host.toCharPtr(), &addr) == 0){
				IPv4Address tmp = IPv4Resolver::resolve(ip_or_host);
				this->operator=(IPv4Resolver::resolve(ip_or_host));
			}
		}

		IPv4Address::IPv4Address(UInt8 a, UInt8 b, UInt8 c, UInt8 d){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_IPv4Address);
#endif
			StringBuffer tmpx;
			tmpx << (int)a << "." << (int)b << "." << (int)c << "." << (int)d;
			String ip_or_host = tmpx.toString();
			bzero(&addr, sizeof(struct ::in_addr));
			if(inet_aton(ip_or_host.toCharPtr(), &addr) == 0){
				IPv4Address tmp = IPv4Resolver::resolve(ip_or_host);
				this->operator=(IPv4Resolver::resolve(ip_or_host));
			}
		}

		IPv4Address::IPv4Address(const IPv4Address &ip){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_IPv4Address);
#endif
			//Util::memcpy< struct ::in_addr >(&addr, &ip.addr, sizeof(::in_addr));
			addr = ip.addr;
		}
		IPv4Address::IPv4Address(const struct ::in_addr *x_addr){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_IPv4Address);
#endif
			//Util::memcpy< ::in_addr >(&addr, x_addr, sizeof(::in_addr));
			addr = *x_addr;
		}
		IPv4Address::~IPv4Address(){
		}
		IPv4Address &IPv4Address::operator=(const struct ::in_addr *_addr){
			//Util::memcpy< ::in_addr >(&addr, _addr, sizeof(::in_addr));
			addr = *_addr;
			return *this;
		}
		IPv4Address &IPv4Address::operator=(const struct ::in_addr &_addr){
			//Util::memcpy< ::in_addr >(&addr, &_addr, sizeof(::in_addr));
			addr = _addr;
			return *this;
		}
		const struct ::in_addr *IPv4Address::address() const{
			return &addr;
		}
		std::string IPv4Address::toString(){
			//String *str_ip;
			char buf[32];
			char *ptr;
			//Generate a string representation of the addr info, I dont know how yet
			//const char * inet_ntop (int AF, const void *CP, char *BUF, size_t LEN)
			ptr = (char *)inet_ntop(AF_INET, (void*)&addr, buf, 32);
			return std::string(ptr);
		}
		std::ostream& operator<<(std::ostream& stream, const IPv4Address &s){
			stream << ((IPv4Address *)&s)->toString().c_str();
			return stream;
		}

	};
};
