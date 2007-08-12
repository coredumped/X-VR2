/*
 * $Id$
 */
#ifndef __XVR2_NETWORK_UDP_H__
#define __XVR2_NETWORK_UDP_H__
#include<xvr2/Object.h>
#include<xvr2/Net/IPv4Address.h>
#include<xvr2/Net/OldUDPSocket.h>
#include<xvr2/Net/OldUDPServerSocket.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2{
	namespace Net{

		class UDP {
			private:
			protected:
			public:
				/** \deprecated This method is going to be dropped in xvr2net from version 0.8.3 ahead.
				 *  please take measures to stop using it. */
				static void send(const OldUDPSocket &s, const void *buf, int size, int flags = 0, int timeout = 0);
				static void send(const IPv4Address &a, int port, const void *buf, int size, int flags = 0, int timeout = 0);
				/** \deprecated This method is going to be dropped in xvr2net from version 0.8.3 ahead.
				 *  please take measures to stop using it. */
				static int receive(const OldUDPServerSocket &s, void *buf, int size, int flags = 0, int timeout = -1);
				static int receive(const IPv4Address &a, int port, void *buf, int size, int flags = 0, int timeout = -1);
				static int receive(int port, void *buf, int size, int flags = 0, int timeout = -1);
		};
	};
};

#endif
