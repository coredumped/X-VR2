/*
 * $Id$
 */
#ifndef __XVR2_UDP_SERVER_SOCKET_H__
#define __XVR2_UDP_SERVER_SOCKET_H__
#include<xvr2/Socket.h>
#include<xvr2/IPv4Address.h>
#include<xvr2/String.h>

namespace xvr2 {
namespace Net {
	class UDPServerSocket : public Socket {
		private:
		protected:
			void bind();
		public:
			UDPServerSocket(int _port);
			UDPServerSocket(const IPv4Address &addr, int _port);
			UDPServerSocket(const String &addr, int _port);
	};
};
};
#endif
