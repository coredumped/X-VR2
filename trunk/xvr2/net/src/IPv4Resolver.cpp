/*
 * $Id$
 */
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include"xvr2/Object.h"
#include"xvr2/System.h"
#include"xvr2/Memory.h"
#include<xvr2/IPv4Address.h>
#include"xvr2/IPv4Resolver.h"
#include<xvr2/HostNotFoundException.h>
#include<xvr2/NSTryAgainException.h>
#include<xvr2/NSFatalException.h>
#include<xvr2/NoIPForYouException.h>

namespace xvr2 {
namespace Net {
	IPv4Address *IPv4Resolver::resolve(const String &ip_or_host){
		IPv4Address *ipv4;
		struct ::hostent ret;
		int h_errnop;
		char *tmp_buf;
		int tmp_blen;
		int bmem;
		struct ::hostent *hp;
		struct ::sockaddr_in name;
		bmem = 2 * ip_or_host.size() + sizeof(hostent) ;
		tmp_blen = bmem;
		while(true){
			tmp_buf = (char *)Memory::allocBuffer(tmp_blen);
			
			if(gethostbyname_r(ip_or_host.toCharPtr(), &ret, tmp_buf, tmp_blen, &hp, &h_errnop) != ERANGE){

				break;
			}
			else {
				tmp_blen += bmem;
				Memory::freeBuffer((void **)&tmp_buf);
			}
			switch(h_errnop){
				case HOST_NOT_FOUND:
					Memory::freeBuffer((void **)&tmp_buf);
					throw Exception::HostNotFound();
					break;
				case TRY_AGAIN:
					Memory::freeBuffer((void **)&tmp_buf);
					throw Exception::NSTryAgain();
					break;
				case NO_RECOVERY:
					Memory::freeBuffer((void **)&tmp_buf);
					throw Exception::NSFatal();
					break;
				case NO_ADDRESS:
					Memory::freeBuffer((void **)&tmp_buf);
					throw Exception::NoIPForYou();
					break;
			}
		}
		if(hp != NULL){
			name.sin_family = AF_INET;
			name.sin_addr = *(struct in_addr *) hp->h_addr;
			ipv4 = new IPv4Address(&name);
		}
		else{
			ipv4 = 0;
		}
		Memory::freeBuffer((void **)&tmp_buf);
		return ipv4;
	}
};
};
