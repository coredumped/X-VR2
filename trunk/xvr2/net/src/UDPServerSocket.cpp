/*
 * $Id$
 */
#include"xvr2/Socket.h"
#include"xvr2/UDPSocket.h"
#include"xvr2/UDPServerSocket.h"
#include"xvr2/IPv4Address.h"
#include"xvr2/String.h"
#include"xvr2/Mutex.h"
#include<sys/poll.h>
#include"xvr2/UDPReceiveTimeoutException.h"

namespace xvr2 {
	namespace Net {
#ifndef XVR2_THREAD_UNSAFE
		xvr2::Mutex udtimx;
#endif

		int UDPServerSocket::getRecvTimeout(){
#ifdef XVR2_THREAD_UNSAFE
			return UDPServerSocket::recvTimeout;
#else
			int t;
			udtimx.lock();
			t = UDPServerSocket::recvTimeout;
			udtimx.unlock();
			return t;
#endif
		}

		void UDPServerSocket::setRecvTimeout(int t){
#ifndef XVR2_THREAD_UNSAFE
			udtimx.lock();
#endif
			UDPServerSocket::recvTimeout = t;
#ifndef XVR2_THREAD_UNSAFE
			udtimx.unlock();
#endif
		}


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
			flags = MSG_NOSIGNAL;
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
			flags = MSG_NOSIGNAL;
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
			flags = MSG_NOSIGNAL;
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
		int UDPServerSocket::receive(void *buf, int size){
			::socklen_t ret;
			struct pollfd fd;
			struct sockaddr_in peer;
			int bytes;
			fd.fd = tsock;
			fd.events = POLLIN | POLLPRI;
			ret = sizeof(struct ::sockaddr_in);
			if(poll(&fd, 1, UDPServerSocket::getRecvTimeout()) == 0){
				throw Exception::UDPReceiveTimeout();
			}
			bytes = ::recvfrom(tsock, buf, size, flags, (struct ::sockaddr *)&peer, &ret);
			if(bytes < -1){
				switch(errno){
					case ECONNRESET:
						throw Exception::ConnectionResetByPeer();
					case ENOMEM:
						throw Exception::Memory();
					default:
						throw Exception::Network();
				}
			}
			return bytes;
		}
	};
};
