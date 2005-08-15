/*
 * $Id$
 */
#include"xvr2/Socket.h"
#include"xvr2/UDPSocket.h"
#include"xvr2/UDPServerSocket.h"
#include"xvr2/IPv4Address.h"
#include"xvr2/String.h"

namespace xvr2 {
	namespace Net {

		void UDPServerSocket::bind(){
			if (::bind(tsock,(struct sockaddr *)&ipv4addr,sizeof(struct ::sockaddr_in))<0) {
				switch(errno){
					case EINVAL:
						throw Exception::SocketAlreadyBounded();
						break;
					default:
						throw Exception::Network();
				}
			}
		}
		UDPServerSocket::UDPServerSocket(int _port){
			port = _port;
			bzero(&ipv4addr, sizeof(struct ::sockaddr_in));
			ipv4addr.sin_family = AF_INET;
			ipv4addr.sin_port = htons(_port);
			ipv4addr.sin_addr.s_addr = INADDR_ANY;
			tsock = socket(ipv4addr.sin_family, SOCK_DGRAM, 0);
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
			bind();
		}
		UDPServerSocket::UDPServerSocket(const IPv4Address &addr, int _port){
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
			bind();
		}
		UDPServerSocket::UDPServerSocket(const String &_addrs, int _port){
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
			bind();
		}
	};
};
