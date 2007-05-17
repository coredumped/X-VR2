/*
 * $Id$
 * This is the socket's parent class
 */

#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2netClassNames.h"
#include"Socket.h"
#include<xvr2/Thread.h>
#ifdef UNIX_SOCKETS
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/tcp.h>
#include<netdb.h>
#else

#endif
#include<iostream>

#include<xvr2/DebugConsole.h>
#include<xvr2/String.h>
#include<xvr2/ThreadManager.h>
#include"IPv4Address.h"
#include<limits.h>

namespace xvr2{
	namespace Net{

		Socket::Socket(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Net_Socket);
#endif
		}

		Socket::~Socket(){
		}

		const int Socket::getSocketID(){
			return tsock;
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
