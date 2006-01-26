/*
 * $Id$
 */
#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__
#include<xvr2/Object.h>
#include<xvr2/DataTypes.h>
#include<xvr2/IPv4Address.h>
#include<xvr2/NetworkExceptions.h>

namespace xvr2{
	namespace Net{
		class UDP;

		/**
		 * This is the socket parent class, this one contains
		 * info and methods shared by client and server sockets
		 */
		class Socket:public Object{
			friend class UDP;
			protected:
				/** This file descriptor represents the 
				 * socket itself as returned
				 * by socket(2) and accept(2)
				 */
				int tsock;
				struct ::sockaddr_in ipv4addr;
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
				void debugmsgln(Socket *, const char *msg);
			public:
				Socket();
				/*Socket(const IPv4Address &addr, int _port);
				Socket(int _port);*/
				~Socket();
				/** Returns the socket's file descriptor 
				 *  value */
				const int getSocketID(){
					return tsock;
				}
				/** Defines the timeout before closing 
				 *  connection to the other end
				 *  of communication*/
				int setSoTimeout(int);
		};
	};
};

#endif
