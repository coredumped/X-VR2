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

#include"xvr2/DebugConsole.h"
#include"xvr2/String.h"
#include"xvr2/ThreadManager.h"
#include"xvr2/IPv4Address.h"

namespace xvr2{
	namespace Net{

		Socket::Socket(){
#ifndef USING_GCC3
			setClassName(xvr2::_xvr2Socket);
#endif
		}

		Socket::~Socket(){
		}

		void Socket::debugmsg(Socket *obj, const char *msg){
			if(obj == 0)
				return;
			//xvr2::String s;
			debugConsole << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid=";
			if(ThreadManager::getCurrentThreadID() == 0){
				debugConsole << "MAIN";
			}
			else{
				debugConsole << (unsigned int)ThreadManager::getCurrentThreadID();
			}
			debugConsole << ",sockid=" << (int)tsock << "]: " << msg;
		}

		void Socket::debugmsgln(Socket *obj, const char *msg){
			if(obj == 0)
				return;
			debugmsg(obj, msg);
			debugConsole << "\n";
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
