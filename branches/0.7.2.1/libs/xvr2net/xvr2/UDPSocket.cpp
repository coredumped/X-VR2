/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include<xvr2/String.h>
#include"IPv4Address.h"
#include"Socket.h"
#include"UDPSocket.h"
#ifndef XVR2_THREAD_UNSAFE
#include"xvr2/Mutex.h"
#endif
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<strings.h>

namespace xvr2 {
	namespace Net {
#ifndef XVR2_THREAD_UNSAFE
		xvr2::Mutex udtim;
#endif

		static int sendTimeout;

		int UDPSocket::getSendTimeout(){
#ifdef XVR2_THREAD_UNSAFE
			return sendTimeout;
#else
			int t;
			udtim.lock();
			t = sendTimeout;
			udtim.unlock();
			return t;
#endif
		}

		void UDPSocket::setSendTimeout(int t){
#ifndef XVR2_THREAD_UNSAFE
			udtim.lock();
#endif
			sendTimeout = t;
#ifndef XVR2_THREAD_UNSAFE
			udtim.unlock();
#endif
		}

		UDPSocket::~UDPSocket(){
		}

		UDPSocket::UDPSocket():Socket(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_UDPSocket);
#endif
			flags = MSG_NOSIGNAL;
		}
		UDPSocket::UDPSocket(const String &_addrs, int _port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_UDPSocket);
#endif
			IPv4Address addr(_addrs);
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
		}
		UDPSocket::UDPSocket(const IPv4Address &addr, int _port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_UDPSocket);
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
		}
		void UDPSocket::send(const void *buf, int size){
			int r;
			r = ::sendto(tsock, buf, size, flags, (struct ::sockaddr *)&ipv4addr, sizeof(ipv4addr));
			if(r == -1){
				switch(errno){
					case ECONNRESET:
						throw ConnectionResetByPeer();
					case ENOMEM:
						throw MemoryException();
					default:
						throw NetworkException();
				}
			}
		}
	};
};
