/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include"xvr2/Socket.h"
#include"xvr2/UDPSocket.h"
#include"xvr2/UDPServerSocket.h"
#include"xvr2/IPv4Address.h"
#include"xvr2/String.h"
#include"xvr2/Mutex.h"
#include<sys/poll.h>
#include<errno.h>
#include<strings.h>

namespace xvr2 {
	namespace Net {
#ifndef XVR2_THREAD_UNSAFE
		xvr2::Mutex udtimx;
#endif

		static int recvTimeout;

		int UDPServerSocket::getRecvTimeout(){
#ifdef XVR2_THREAD_UNSAFE
			return recvTimeout;
#else
			int t;
			udtimx.lock();
			t = recvTimeout;
			udtimx.unlock();
			return t;
#endif
		}

		void UDPServerSocket::setRecvTimeout(int t){
#ifndef XVR2_THREAD_UNSAFE
			udtimx.lock();
#endif
			recvTimeout = t;
#ifndef XVR2_THREAD_UNSAFE
			udtimx.unlock();
#endif
		}


		void UDPServerSocket::bind(){
			if (::bind(tsock,(struct sockaddr *)&ipv4addr,sizeof(struct ::sockaddr_in))<0) {
				switch(errno){
					case EINVAL:
						throw SocketAlreadyBounded();
						break;
					default:
						throw NetworkException();
				}
			}
		}
		UDPServerSocket::UDPServerSocket(int _port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_UDPServerSocket);
#endif
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
						throw ProcOutOfFileDescriptors();
					break;
					case ENFILE:
						throw SysOutOfFileDescriptors();
					break;
					default:
						throw IOException();
				}
			}
			bind();
		}
		UDPServerSocket::UDPServerSocket(const IPv4Address &addr, int _port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_UDPServerSocket);
#endif
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
						throw ProcOutOfFileDescriptors();
					break;
					case ENFILE:
						throw SysOutOfFileDescriptors();
					break;
					default:
						throw IOException();
				}
			}
			bind();
		}
		UDPServerSocket::UDPServerSocket(const String &_addrs, int _port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_UDPServerSocket);
#endif
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
						throw ProcOutOfFileDescriptors();
					break;
					case ENFILE:
						throw SysOutOfFileDescriptors();
					break;
					default:
						throw IOException();
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
				throw UDPReceiveTimeout();
			}
			bytes = ::recvfrom(tsock, buf, size, flags, (struct ::sockaddr *)&peer, &ret);
			if(bytes < -1){
				switch(errno){
					case ECONNRESET:
						throw ConnectionResetByPeer();
					case ENOMEM:
						throw MemoryException();
					default:
						throw NetworkException();
				}
			}
			return bytes;
		}
		int UDPServerSocket::peek(void *buf, int size){
			int fx = flags;
			int ret;
			flags |= MSG_PEEK;
			ret = receive(buf, size);
			flags = fx;
			return ret;
		}
	};
};
