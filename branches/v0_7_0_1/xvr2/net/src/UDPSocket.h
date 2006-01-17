/*
 * $Id$
 */
#ifndef __XVR2_UDP_SOCKET_H__
#define __XVR2_UDP_SOCKET_H__
#include<xvr2/Socket.h>
#include<xvr2/IPv4Address.h>
#include<xvr2/String.h>
#include<xvr2/ConnectionResetByPeerException.h>
#include<xvr2/NetworkException.h>
#include<xvr2/MemoryException.h>

namespace xvr2 {
namespace Net {
	class UDPSocket : public Socket {
		private:
			friend class UDPServerSocket;
		protected:
			int flags;
		public:
			UDPSocket();
			UDPSocket(const String &_addr, int _port);
			UDPSocket(const IPv4Address &_addr, int _port);
			virtual ~UDPSocket();
			static void setSendTimeout(int t);
			static int  getSendTimeout();
			virtual void send(const void *buf, int size);
			template<class T>
			void send(const T *buf){
				send((void *)buf, sizeof(T));
			}
	};
};
};

#endif
