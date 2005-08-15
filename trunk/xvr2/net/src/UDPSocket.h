/*
 * $Id$
 */
#ifndef __XVR2_UDP_SOCKET_H__
#define __XVR2_UDP_SOCKET_H__
#include<xvr2/Socket.h>
#include<xvr2/IPv4Address.h>
#include<xvr2/String.h>

namespace xvr2 {
namespace Net {
	class UDPSocket : public Socket {
		private:
		protected:
		public:
			UDPSocket();
			UDPSocket(const String &_addr, int _port);
			UDPSocket(const IPv4Address &_addr, int _port);
	};
};
};

#endif
