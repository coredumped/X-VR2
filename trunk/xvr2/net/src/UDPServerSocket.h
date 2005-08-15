/*
 * $Id$
 */
#ifndef __XVR2_UDP_SERVER_SOCKET_H__
#define __XVR2_UDP_SERVER_SOCKET_H__
#include<xvr2/Socket.h>
#include<xvr2/UDPSocket.h>
#include<xvr2/IPv4Address.h>
#include<xvr2/String.h>
#include<xvr2/UDPReceiveTimeoutException.h>

namespace xvr2 {
namespace Net {
	class UDPServerSocket : public Socket {
		private:
		protected:
			int flags;
			static int recvTimeout;
			void bind();
		public:
			UDPServerSocket(int _port);
			UDPServerSocket(const IPv4Address &addr, int _port);
			UDPServerSocket(const String &addr, int _port);
			static void setRecvTimeout(int t);
			static int  getRecvTimeout();
			virtual int receive(void *buf, int size);
	};
};
};
#endif
