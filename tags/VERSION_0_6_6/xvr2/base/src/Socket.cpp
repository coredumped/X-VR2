/*
 * $Id$
 * This is the socket's parent class
 */

#include"Socket.h"
#include"Thread.h"
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
#include<Console.h>
#include<String.h>
#endif

namespace xvr2{
	namespace Network{

		Socket::Socket(){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2Socket);
#endif
		}

		void Socket::debugmsg(Socket *obj, const char *msg){
#ifdef USE_DEBUG
		xvr2::String s;
		s = obj->getClassName();
		s += "[ptr=";
		s.concat((unsigned int)obj);
		s += ",tid=";
		s.concat((unsigned int)pthread_self());
		s += ",sockid=";
		s.concat((int)tcpsock);
		s += "]: ";
		__debug_console.errWrite(s);
		__debug_console.errWrite(msg);
#else
			std::cout << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid: " << Thread::numericID() << ",sockid=" << tcpsock << "]: " << msg;
			std::cout.flush();
#endif
		}
		
		int Socket::setSockOption(int opname, void *optval, 
						unsigned int siz){
#ifdef UNIX_SOCKETS
#ifdef SOLARIS
				char *optval1;
				optval1 = (char *)optval;
				return setsockopt(tcpsock, SOL_SOCKET, 
						opname, optval1, 
						siz);
#else
				return setsockopt(tcpsock, SOL_SOCKET, 
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
			return setsockopt(tcpsock, SOL_TCP, opname, optval, 
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
