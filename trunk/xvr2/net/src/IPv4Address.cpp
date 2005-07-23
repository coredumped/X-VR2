/*
 * $Id$
 */
#include"xvr2/IPv4Address.h"
#include"xvr2/Memory.h"
#include<errno.h>

namespace xvr2 {
namespace Net {

	IPv4Address::IPv4Address(const String &ip_or_host){
		IPv4Address *tmp;
		try{
			tmp = IPv4Resolver::resolve(ip_or_host);
			addr.sin_addr = tmp->addr.sin_addr;
			addr.sin_family = tmp->addr.sin_family;
			delete tmp;
		}
		catch(...){
			delete tmp;
			throw;
		}
	}
	IPv4Address::IPv4Address(UInt8 a, UInt8 b, UInt8 c, UInt8 d){
		String tmpx((int)a);
		tmpx.concat((int)b);
		tmpx.concat((int)c);
		tmpx.concat((int)d);
		IPv4Address *tmp;
		try{
			tmp = IPv4Resolver::resolve(tmpx);
			addr.sin_family = tmp->addr.sin_family;
			addr.sin_addr = tmp->addr.sin_addr;
			delete tmp;
		}
		catch(...){
			delete tmp;
			throw;
		}
	}
	IPv4Address::IPv4Address(const IPv4Address &ip){
		addr.sin_addr = ip.sockAddr().sin_addr;
		addr.sin_family = ip.sockAddr().sin_family;
	}
	IPv4Address::IPv4Address(const struct ::sockaddr_in *x_addr){
		addr.sin_addr = x_addr->sin_addr;
		addr.sin_family = x_addr->sin_family;
	}
	IPv4Address::~IPv4Address(){
	}
	const struct ::sockaddr_in IPv4Address::sockAddr() const{
		return addr;
	}
	String *IPv4Address::toString(){
		String *str_ip;
		//Generate a string representation of the addr info, I dont know how yet
		return str_ip;
	}
	std::ostream& operator<<(std::ostream& stream, const IPv4Address &s){
		char *thedata;
		stream << thedata;
	}

};
};
