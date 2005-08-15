/*
 * $Id$
 * This is the socket's parent class
 */

#include"xvr2/Socket.h"
#include"xvr2/Thread.h"
#ifdef UNIX_SOCKETS
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/tcp.h>
#include<netdb.h>
#else
#include <SDL_net.h>
#endif
#include<iostream>

#ifdef USE_DEBUG
#include"xvr2/Console.h"
#include"xvr2/String.h"
#include"xvr2/ThreadManager.h"
#endif
#include"xvr2/IPv4Address.h"

namespace xvr2{
	namespace Net{

		Socket::Socket(){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2Socket);
#endif
		}

		/*Socket::Socket(int _port){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2Socket);
#endif
			port = _port;
			bzero(&ipv4addr, sizeof(struct ::sockaddr_in));
			ipv4addr.sin_family = AF_INET;
			ipv4addr.sin_port = htons(_port);
			ipv4addr.sin_addr.s_addr = INADDR_ANY;
			tsock = socket(ipv4addr.sin_family, SOCK_DGRAM, 0);
			if (bind(tsock,(struct sockaddr *)&ipv4addr,sizeof(struct ::sockaddr_in))<0) {
				switch(errno){
					case EINVAL:
						throw Exception::SocketAlreadyBounded();
						break;
					default:
						throw Exception::Network();
				}
			}
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
		}*/

		Socket::~Socket(){
		}

		void Socket::debugmsg(Socket *obj, const char *msg){
#ifdef USE_DEBUG
			xvr2::String s;
			s = obj->getClassName();
			s += "[ptr=";
			s.concat((unsigned int)obj);
			s += ",tid=";
			//s.concat((unsigned int)pthread_self());
			if(ThreadManager::getCurrentThread() == 0){
				s.concat("MAIN");
			}
			else{
				s.concat((unsigned int)ThreadManager::getCurrentThread());
			}
			s += ",sockid=";
			s.concat((int)tsock);
			s += "]: ";
			__debug_console.errWrite(s);
			__debug_console.errWrite(msg);
#else
			std::cout << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid: " << Thread::numericID() << ",sockid=" << tsock << "]: " << msg;
			std::cout.flush();
#endif
		}

		void Socket::debugmsgln(Socket *obj, const char *msg){
#ifdef USE_DEBUG
			xvr2::String s;
			s = obj->getClassName();
			s += "[ptr=";
			s.concat((unsigned int)obj);
			s += ",tid=";
			//s.concat((unsigned int)pthread_self());
			if(ThreadManager::getCurrentThread() == 0){
				s.concat("MAIN");
			}
			else{
				s.concat((unsigned int)ThreadManager::getCurrentThread());
			}
			s += ",sockid=";
			s.concat((int)tsock);
			s += "]: ";
			__debug_console.errWrite(s);
			__debug_console.errWrite(msg);
			__debug_console.errWrite("\n");
#else
			std::cout << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid: " << Thread::numericID() << ",sockid=" << tsock << "]: " << msg << std::endl;
#endif
		}
		
		int Socket::setSockOption(int opname, void *optval, 
						unsigned int siz){
#ifdef UNIX_SOCKETS
#ifdef SOLARIS
				char *optval1;
				optval1 = (char *)optval;
				return setsockopt(tsock, SOL_SOCKET, 
						opname, optval1, 
						siz);
#else
				return setsockopt(tsock, SOL_SOCKET, 
						opname, optval, 
						siz);
#endif
#else
			return 0;
#endif
		}
		
		int Socket::setTCPOption(int opname, void *optval, 
						unsigned int siz){
#ifdef UNIX_SOCKETS
			return setsockopt(tsock, SOL_TCP, opname, optval, 
					sizeof(optval));
#else
			return 0;
#endif
		}
		
		int Socket::setSoTimeout(int t){
#ifdef UNIX_SOCKETS
			return setSockOption(SO_KEEPALIVE, &t, sizeof(int));
#endif
			return 0;
		}

	};
};
