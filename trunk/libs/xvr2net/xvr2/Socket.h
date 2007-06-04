/* $Id$ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef __XVR2_NET_SOCKET_H__
#define __XVR2_NET_SOCKET_H__
#include<xvr2/Object.h>
#include<xvr2/Net/SocketExceptions.h>
#include<xvr2/Net/IPv4Address.h>
#include<xvr2/FileException.h>
#include<sys/types.h>
#include<sys/socket.h>

namespace xvr2 {
	namespace Net {

		/** \class Socket Socket.h <xvr2/Net/Socket.h>
		 * Network sockets main interface class. */
		class Socket:public Object {
			private:
			protected:
				/** This is the socket file descriptor per se. */
				int _socket;
				/** Controls wheter this is an ipv4 socket or not, if not, then it
				 *  is considered to be ipv6. */
				bool is_ipv4;
				/** Polymorphic socket creation method.
				 *  Each Socket subclass must provide its own socket creation method according
				 *  to the protocol their handling.
				 *  Internally this method only takes care of creating the socket file destriptor
				 *  and setting some basic options depending on the protocol to be used. */
				virtual void create(int protoid = 0) = 0;
				/** Retrieves the value of the specified option at the given level for this socket.
				 *  \param level Option level, OS-dependent.
				 *  \param optname Option name to be changed.
				 *  \param optval Holds the buffer where value will be saved.
				 *  \param optlen Is the output buffer size.
				 *  \exception xvr2::Net::SocketOptionException
				 *  \exception xvr2::Net::SocketOptionParamFailure
				 *  \exception xvr2::Net::SocketOptionIsInvalid */
				virtual void getsockopt(int level, int optname, void *optval, socklen_t *optlen);
				/** Sets the value of the specified option at the given level for this socket.
				 *  @param level Option level, OS-dependent.
				 *  @param optname Option name to be changed.
				 *  @param optval Value to set the option.
				 *  @param optlen Holds the optval datasize.
				 *  @exception xvr2::Net::SocketOptionException
				 *  @exception xvr2::Net::SocketOptionParamFailure
				 *  @exception xvr2::Net::SocketOptionIsInvalid */
				virtual void setsockopt(int level, int optname, const void *optval, socklen_t optlen);
			public:
				/** Default constructor. */
				Socket();
				/** Copy constructor.
				 *  Builds a new Socket instance from another.
				 *  @param s Source socket object from where we will be
				 *  intantiating. */
				Socket(const Socket &s);
				/** Virtual destructor. */
				virtual ~Socket();
				/** Closes the socket so it wont send nor receive data. */
				virtual void close();
				/** \e Binds this socket to a specified address.
				 *  Binding will let you configure this socket to listen
				 *  or send data from a specific local address, very useful
				 *  for server applications on machines with multiple interfaces
				 *  since sometimes you just want to send/receive data to/from
				 *  a specific interface, however the same can be done with
				 *  client apps.
				 *  @param ip IP address assigned to the local interface to be 
				 *  binded from. */
				void bind(const IPv4Address &ip);
				/** Puts or takes out the socket from debug mode.
				 *  This method will activate the recording of debug information based on
				 *  the used protocol, use this method carefully it is very OS dependent.
				 *  @param[in] enabled If true it will enable debug mode for the socket, if false it
				 *  will disable debug mode.
				 *  @return The previous debug mode state. */
				bool debug(bool enabled);
				/** Tells wheter the socket is currently in debug mode or not.
				 *  @return true if the socket is in debug mode, false otherwise */
				bool debug();
				/** Activates port re-usage, use with care.
				 *  This method will allow a port to be re-used even if
				 *  the socket has already been binded, as a result you
				 *  can have multiple sockets binded to the same port.
				 *  @param enabled If true enables port reuse.
				 *  @return The previous value. */
				bool reuseAddr(bool enabled);
				/** Tells wheter this socket has a reusable port or not.
				 *  @return true if it is reusable, false if not. */
				bool reuseAddr();
				/** Enables connection keepalive if the protocol supports it.
				 *  This option activates/deactivates sending keepalives to the
				 *  remote peer, this keepalives are messages sent peridically
				 *  in order to determine if the connection has benn broken or 
				 *  not, if a response to the message is not recieved, then
				 *  the connection is considered broken.
				 *  @param enabled If true, the keepalive function will be
				 *  enabled, if false then it will be disabled.
				 *  @return The previous value. */
				bool keepalive(bool enabled);
				/** Tells wheter the socket is using keepalives or not.
				 *  @return true if keepalives are active, false otherwise. */
				bool keepalive();
				/** Tells the socket to send data directly to the peer interface
				 *  bypassing any routin facilities.
				 *  @param enabled If true, the messages will be sent directly
				 *  to the peer interface, if false outgoing messages won't 
				 *  bypass routing.
				 *  @return The previous value. */
				bool dontroute(bool enabled);
				/** Tell wheter this socket is bypassing routing or not.
				 *  @return true if it is bypassing routing, false if not . */
				bool dontroute();
				/** Controls what to do when the connection is closed and there's
				 *  still data waiting to sent over the channel.
				 *  \param enabled if true the close() method will get blocked
				 *  until all data has benn transmited to the other side, if false
				 *  then a call close will return inmediately or until the secs
				 *  period has expired.
				 *  \param secs timeout before effectively closing the socket in
				 *  case it still has messages to send. */
				void linger(bool enabled, int secs = 1);
				/** Tells wheter this socket is lingering.
				 *  \return 0 if it is not lingering, otherwise the number of
				 *  seconds used as timeout before effectively closing the channel. */
				int linger();
				/** Enables transmision broadcast for datagram based sockets.
				 *  \param enabled If true, datagram broadcasting is enabled, if
				 *  false then it will be disabled.
				 *  @return The previous value. */
				bool broadcast(bool enabled);
				/** Tells wheter broadcasting has been enabled for this socket or not.
				 *  \return true if bradcasts are enabled, false otherwise. */
				bool broadcast();
				/** Enables the recival of out of band (urgent) data in the same channel
				 *  we're reading, use with care.
				 *  \param enabled if true enables  inline out of band receiving, if false
				 *  disables it. */
				bool recvOOBInline(bool enabled);
				/** Tells wheter the receival of out of band data is enabled or not.
				 *  \return true if is enabled, false otherwise. */
				bool recvOOBInline();
				/** Changes the send buffer size value. 
				 *  @return the previous value. */
				int sendBufSize(int newsize);
				/** Tells how big is the send buffer size.
				 *  @return send buffer size in bytes. */
				int sendBufSize();
				/** Changes the receive buffer size value. 
				 *  @return the previous value. */
				int recvBufSize(int newsize);
				/** Tells how big is the receive buffer size.
				 *  @return send buffer size in bytes. */
				int recvBufSize();
				/** Tells wheter this is a stream socket (a connected socket).
				 *  @return true if it is a stream socket, false if not. */
				bool isStream();
				/** Tells wheter this is a datagram socket.
				 *  A datagram is a communication style whose purpose is to send 
				 *  individually addressed packets unreliably (much like UDP).
				 *  @return true if this is a datagram socket, false if not. */
				bool isDatagram();
				/** Tells wheter this is a raw socket.
				 *  Raw sockets are used to access low-level features of communication
				 *  protocols, sniffer and other type of applications use this type
				 *  of communication.
				 *  @return true if it is a raw socket, false if not. */
				bool isRaw();
				/** Tells wheter this socket has been created to be used with
				 *  ipv4 naming space conventions. */
				bool isIPv4();
				/** Tells wheter this socket has been created to be used with
				 *  ipv6 naming space conventions. */
				bool isIPv6();
		};

	};
};

#endif

