/*
 * $Id$
 */
#ifndef __XVR2_OLD_UDP_SERVER_SOCKET_H__
#define __XVR2_OLD_UDP_SERVER_SOCKET_H__
#include<xvr2/String.h>
#include<xvr2/Net/OldSocket.h>
#include<xvr2/Net/OldUDPSocket.h>
#include<xvr2/Net/IPv4Address.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2 {
	namespace Net {
		/** \class OldUDPServerSocket OldUDPServerSocket.h <xvr2/Net/OldUDPServerSocket.h>
		 *  \brief UDP server side class, it takes care of receiving UDP messages.
		 *  \deprecated This class will be dropped as of xvr2net version
		 *  8.0.3 please migrate your code before that, it has only been
		 *  kept for compatibility with previous releases. */
		class OldUDPServerSocket : public OldSocket {
			private:
			protected:
				int flags;
				void bind();
			public:
				OldUDPServerSocket(int _port);
				OldUDPServerSocket(const IPv4Address &addr, int _port);
				OldUDPServerSocket(const String &addr, int _port);
				static void setRecvTimeout(int t);
				static int  getRecvTimeout();
				int peek(void *buf, int size);
				virtual int receive(void *buf, int size);
				template<class T>
				int receive(T *buf){
					return receive((void *)buf, sizeof(T));
				}
				template<class T>
				int peek(T *buf){
					return peek((void *)buf, sizeof(T));
				}
		};
	};
};
#endif

