/*
 * $Id$
 */
#ifndef __XVR2_OLD_UDP_SOCKET_H__
#define __XVR2_OLD_UDP_SOCKET_H__
#include<xvr2/String.h>
#include<xvr2/Net/OldSocket.h>
#include<xvr2/Net/IPv4Address.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2 {
	namespace Net {
		/** \class OldUDPSocket OldUDPSocket.h <xvr2/Net/OldUDPSocket.h>
		 *  \brief UDP client side class, it takes care of sending UDP messages.
		 *  \deprecated This class will be dropped as of xvr2net version
		 *  8.0.3 please migrate your code before that, it has only been
		 *  kept for compatibility with previous releases. */
		class OldUDPSocket : public OldSocket {
			private:
				friend class UDPServerSocket;
			protected:
				int flags;
			public:
				OldUDPSocket();
				OldUDPSocket(const String &_addr, int _port);
				OldUDPSocket(const IPv4Address &_addr, int _port);
				virtual ~OldUDPSocket();
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

