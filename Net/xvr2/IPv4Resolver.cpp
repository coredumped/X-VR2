/*
 * $Id$
 */
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/Object.h>
#include<xvr2/System.h>
#include<xvr2/Memory.h>
#include"_xvr2netClassNames.h"
#include"IPv4Address.h"
#include"IPv4Resolver.h"
#include<errno.h>

namespace xvr2 {
	namespace Net {
		IPv4Address IPv4Resolver::resolve(const String &ip_or_host){
			struct ::hostent ret;
			int h_errnop;
			char *tmp_buf;
			int tmp_blen;
			int bmem;
			struct ::hostent *hp;
			struct ::sockaddr_in name;
			bzero(&name, sizeof(struct ::sockaddr_in));
			int result;
			bmem = 4 * ip_or_host.size() + 2 * sizeof(hostent) ;
			tmp_blen = bmem;
			while(true){
				tmp_buf = new char[tmp_blen];
				result = gethostbyname_r(ip_or_host.toCharPtr(), &ret, tmp_buf, tmp_blen, &hp, &h_errnop);
				if(result == ERANGE){
					tmp_blen += bmem;
					delete[] tmp_buf;
					continue;
				}
				switch(h_errnop){
					case HOST_NOT_FOUND:
						delete[] tmp_buf;
						throw HostNotFound();
						break;
					case TRY_AGAIN:
						delete[] tmp_buf;
						throw NSTryAgain();
						break;
					case NO_RECOVERY:
						delete[] tmp_buf;
						throw NSFatal();
						break;
					case NO_ADDRESS:
						delete[] tmp_buf;
						throw NoIPForYou();
						break;
				}
				break;
			}
			if(hp != NULL){
				name.sin_family = AF_INET;
				name.sin_addr = *(struct in_addr *) hp->h_addr;
			}
			delete[] tmp_buf;
			return IPv4Address(&name.sin_addr);
		}

		/*static String *IPv4Address::reverse_lookup(const String &ip_address){
			String *h = 0;

			return h;
		}*/
	};
};
