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
#ifndef __XVR2_NET_CLIENT_SOCKET_H__
#define __XVR2_NET_CLIENT_SOCKET_H__
#include<xvr2/Net/RawSocketInputStream.h>
#include<xvr2/Net/RawSocketOutputStream.h>
#include<xvr2/Net/Socket.h>
#include<xvr2/Net/IPv4Address.h>

namespace xvr2 {
	namespace Net {

		/** \interface ClientSocket ClientSocket.h <xvr2/Net/ClientSocket.h>
		 *  Abstract client socket class. */
		class ClientSocket:public Socket {
			private:
			protected:
				/** Output stream object. */
				RawSocketInputStream out;
				/** Input stream object. */
				RawSocketOutputStream in;
			public:
				/** Default constructor. */
				ClientSocket();
				/** Mandatory destructor. */
				virtual ~ClientSocket();
				/** Abstract connect method, use the one from a derived
				 *  class instead. */
				virtual void connect(const IPv4Address &addr, int port) = 0;
				/** Returns the associated input address for writing operations.
				 *  \return a stream from where you can send data through this
				 *  socket. */
				RawSocketOutputStream &inputStream();
				/** Returns the associated output address for reading operations.
				 *  \return a stream from where you can receive data through this
				 *  socket. */
				RawSocketInputStream &outputStream();
		};
	};
};

#endif

