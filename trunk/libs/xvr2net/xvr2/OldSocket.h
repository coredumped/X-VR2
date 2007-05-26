/*
 * $Id$
 */
#ifndef __OLD_SOCKET_BASE_H__
#define __OLD_SOCKET_BASE_H__
#include<xvr2/Object.h>
#include<xvr2/DataTypes.h>
#include<xvr2/Net/IPv4Address.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2{
	namespace Net{
		class UDP;

		/** \class OldSocket OldSocket.h <xvr2/Net/OldSocket.h>
		 *  \brief This is the socket parent class, this one contains
		 *  info and methods shared by client and server sockets
		 *  \deprecated This class will be dropped as of xvr2net version
		 *  8.0.3 please migrate your code before that, it has only been
		 *  kept for compatibility with previous releases.
		 */
		class OldSocket:public Object{
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

				/** For debugging purposes only */
				String string_representation;
			public:
				OldSocket();
				/*OldSocket(const IPv4Address &addr, int _port);
				OldSocket(int _port);*/
				~OldSocket();
				/** Returns the socket's file descriptor 
				 *  value */
				const int getSocketID();
				/** Defines the timeout before closing 
				 *  connection to the other end
				 *  of communication*/
				int setSoTimeout(int);
		};
	};
};

#endif
