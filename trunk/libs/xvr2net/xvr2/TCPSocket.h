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
#ifndef __XVR2_NET_TCP_SOCKET_H__
#define __XVR2_NET_TCP_SOCKET_H__
#include<xvr2/Net/ClientSocket.h>
#include<xvr2/Net/IPv4Address.h>

namespace xvr2 {
	namespace Net {
		/** \class TCPSocket TCPSocket.h <xvr2/Net/TCPSocket.h>
		 *  TCP client socket class.
		 *  By working with objects of type TCPSocket you'll be able
		 *  to connect to remote peers via the TCP/IP protocol using
		 *  the a variety of ip address namings, like IPv4 and IPv6. */
		class TCPSocket:public ClientSocket {
			private:
			protected:
				/** Initializes the socket itself, and ensures
				 *  it will be created for use in the internet
				 *  namespace. */
				void create(int protoid = 0);
			public:
				/** Default constructor.
				 *  Initializes the socket but does not connect to
				 *  anything, since a destinarion address and port
				 *  has not been specified. */
				TCPSocket();
				/** Instantiates a TCP socket and connects it to the
				 *  specified internet address and port.
				 *  \param addr IPv4 destination address.
				 *  \param port destination port number. */
				TCPSocket(const IPv4Address &addr, int port);
				/** Copy constructor.
				 *  Instantiates this object from the properties of
				 *  another TCPSocket, the result will be an exact
				 *  copy, this new copy will even share the connection
				 *  state of the socket it was copied from. */
				TCPSocket(const TCPSocket &s);
				/** Instatiates a socket from the given file descriptor id. */
				TCPSocket(int fd);
				/** Mandatory destructor. */
				~TCPSocket();
				/** Connects the specified TCPSocket to the given address.
				 *  \param addr IPv4 destination address.
				 *  \param port destination port number. */
				void connect(const IPv4Address &addr, int port);
		};
	};
};

#endif
