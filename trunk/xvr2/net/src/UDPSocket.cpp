/*
 * $Id$
 */
#include"xvr2/IPv4Address.h"
#include"xvr2/String.h"
#include"xvr2/Socket.h"
#include"xvr2/UDPSocket.h"
#include<sys/socket.h>
#include<sys/types.h>

namespace xvr2 {
	namespace Net {
		UDPSocket::UDPSocket():Socket(){;}
		UDPSocket::UDPSocket(const String &_addrs, int _port){
			IPv4Address addr(_addrs);
			port = _port;
			bzero(&ipv4addr, sizeof(struct ::sockaddr_in));
			ipv4addr.sin_family = addr.sockAddr()->sin_family;
			ipv4addr.sin_port   = htons(_port);
			ipv4addr.sin_addr   = addr.sockAddr()->sin_addr;
			tsock = socket(addr.sockAddr()->sin_family, SOCK_DGRAM, 0);
			if(tsock < 0){
				switch(errno){
					case EMFILE:
						throw Exception::ProcOutOfFileDescriptors();
					break;
					case ENFILE:
						throw Exception::SysOutOfFileDescriptors();
					break;
					default:
						throw Exception::IO();
				}
			}
		}
		UDPSocket::UDPSocket(const IPv4Address &addr, int _port){
			port = _port;
			bzero(&ipv4addr, sizeof(struct ::sockaddr_in));
			ipv4addr.sin_family = addr.sockAddr()->sin_family;
			ipv4addr.sin_port   = htons(_port);
			ipv4addr.sin_addr   = addr.sockAddr()->sin_addr;
			tsock = socket(addr.sockAddr()->sin_family, SOCK_DGRAM, 0);
			if(tsock < 0){
				switch(errno){
					case EMFILE:
						throw Exception::ProcOutOfFileDescriptors();
					break;
					case ENFILE:
						throw Exception::SysOutOfFileDescriptors();
					break;
					default:
						throw Exception::IO();
				}
			}
		}
	};
};
