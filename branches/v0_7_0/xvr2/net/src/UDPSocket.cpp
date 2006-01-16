/*
 * $Id$
 */
#include"xvr2/IPv4Address.h"
#include"xvr2/String.h"
#include"xvr2/Socket.h"
#include"xvr2/UDPSocket.h"
#ifndef XVR2_THREAD_UNSAFE
#include"xvr2/Mutex.h"
#endif
#include<sys/socket.h>
#include<sys/types.h>
#include"xvr2/NetworkException.h"
#include"xvr2/MemoryException.h"
#include<errno.h>

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
			flags = MSG_NOSIGNAL;
		}
		UDPSocket::UDPSocket(const String &_addrs, int _port){
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
		}
		void UDPSocket::send(const void *buf, int size){
			int r;
			r = ::sendto(tsock, buf, size, flags, (struct ::sockaddr *)&ipv4addr, sizeof(ipv4addr));
			if(r == -1){
				switch(errno){
					case ECONNRESET:
						throw Exception::ConnectionResetByPeer();
					case ENOMEM:
						throw Exception::Memory();
					default:
						throw Exception::Network();
				}
			}
		}
	};
};
