/*
 * $Id$
 */
#ifndef __XVR2_NET_SOCKET_H__
#define __XVR2_NET_SOCKET_H__
#include<xvr2/Object.h>
#include<xvr2/Net/SocketExceptions.h>
#include<sys/types.h>
#include<sys/socket.h>

namespace xvr2 {
	namespace Net {

		/** Network sockets main interface class. */
		class Socket:public Object {
			private:
			protected:
				/** This is the socket file descriptor per se. */
				int _socket;
				/** Polymorphic socket creation method.
				 *
				 *  Each Socket subclass must provide its own socket creation method according
				 *  to the protocol their handling.
				 *  Internally this method only takes care of creating the socket file destriptor
				 *  and setting some basic options depending on the protocol to be used. */
				virtual void create() = 0;
				/**
				 *  \exception xvr2::Net::SocketOptionException
				 *  \exception xvr2::Net::SocketOptionParamFailure
				 *  \exception xvr2::Net::SocketOptionIsInvalid */
				virtual void getsockopt(int level, int optname, void *optval, socklen_t *optlen);
				/**
				 *  \exception xvr2::Net::SocketOptionException
				 *  \exception xvr2::Net::SocketOptionParamFailure
				 *  \exception xvr2::Net::SocketOptionIsInvalid */
				virtual void setsockopt(int level, int optname, const void *optval, socklen_t optlen);
			public:
				Socket();
				Socket(const Socket &s);
				virtual ~Socket();
				/** Puts or takes out the socket from debug mode.
				 *
				 *  This method will activate the recording of debug information based on
				 *  the used protocol, use this method carefully it is very OS dependent.
				 *  @param[in] enabled If true it will enable debug mode for the socket, if false it
				 *  will disable debug mode.
				 *  @return The previous debug mode state. */
				bool setDebug(bool enabled);
				/** Tells wheter the socket is currently in debug mode or not.
				 *  @return true if the socket is in debug mode, false otherwise */
				bool debug();
		};

		/** \class Socket Socket.h <xvr2/Net/Socket.h> */
	};
};

#endif

