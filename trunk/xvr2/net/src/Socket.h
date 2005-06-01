/*
 * $Id$
 */
#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__
#include<xvr2/Object.h>
#include<xvr2/DataTypes.h>

namespace xvr2{
	namespace Net{

		/**
		 * This is the socket parent class, this one contains
		 * info and methods shared by client and server sockets
		 */
		class Socket:public Object{
			protected:
				/** This file descriptor represents the 
				 * socket itself as returned
				 * by socket(2) and accept(2)
				 */
				TCPsocket tcpsock;
				/**
				 * Defines the communications port used by
				 * the socket or the port 
				 * which the socket server uses to 
				 * listen requests
				 */
				int port;
				/**
				 * Is an interface to setsockopt
				 */
				int setSockOption(int opname, void *optval, unsigned int siz);
				int setTCPOption(int opname, void *optval, unsigned int siz);
				void debugmsg(Socket *, const char *msg);
			public:
				Socket();
				~Socket(){
				}
				/** Returns the socket's file descriptor 
				 *  value */
				const int getSocketID(){
					return tcpsock;
				}
				/** Defines the timeout before closing 
				 *  connection to the other end
				 *  of communication*/
				int setSoTimeout(int);
		};
	};
};

#endif
