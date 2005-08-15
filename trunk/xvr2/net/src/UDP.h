/*
 * $Id$
 */
#ifndef __XVR2_NETWORK_UDP_H__
#define __XVR2_NETWORK_UDP_H__
#include<xvr2/Object.h>
#include<xvr2/IPv4Address.h>
#include<xvr2/UDPSocket.h>
#include<xvr2/UDPServerSocket.h>
#include<xvr2/UDPReceiveTimeoutException.h>
#include<xvr2/ConnectionResetByPeerException.h>
#include<xvr2/NetworkException.h>
#include<xvr2/MemoryException.h>

namespace xvr2{
namespace Net{

	class UDP {
		private:
		protected:
		public:
			static void send(const UDPSocket &s, const void *buf, int size, int flags = 0, int timeout = 0);
			static void send(const IPv4Address &a, int port, const void *buf, int size, int flags = 0, int timeout = 0);
			static int receive(const UDPServerSocket &s, void *buf, int size, int flags = 0, int timeout = -1);
			static int receive(const IPv4Address &a, int port, void *buf, int size, int flags = 0, int timeout = -1);
			static int receive(int port, void *buf, int size, int flags = 0, int timeout = -1);
	};
};
};

#endif
