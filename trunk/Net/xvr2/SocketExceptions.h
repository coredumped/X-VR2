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
#ifndef __XVR2_NET_SOCKET_EXCEPTIONS_H__
#define __XVR2_NET_SOCKET_EXCEPTIONS_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>
#include<xvr2/Net/NetworkExceptions.h>

namespace xvr2 {
	namespace Net {

		/** \class SocketException SocketExceptions.h <xvr2/Net/SocketExceptions.h>
		 *  Generic parent exception thrown whenever a socket-level operation fails. */
		class SocketException:public NetworkException {
			public:
				/** Default constructor. */
				SocketException();
				SocketException(OSErrorCodeT error_code);
		};

		/** \class SocketOptionException SocketExceptions.h <xvr2/Net/SocketExceptions.h>
		 *  Exception to be thrown whenever a socket option set/get operation fails. */
		class SocketOptionException:public SocketException {
			public:
				/** Default constructor.
				 *
				 *  Initializes internal os_errval to 0, while triggering
				 *  this exception you should consider using the SocketOptionException(int x_errno)
				 *  method instead. */
				SocketOptionException();
				/** Call this constructor always, it will take care of properly
				 *  initializing the internal OS-depend error code representation. */
				SocketOptionException(OSErrorCodeT x_errno);
		};

		/** \class SocketOptionParamFailure SocketExceptions.h <xvr2/Net/SocketExceptions.h>
		 *  Exception thrown after a call to Socket::setsockopt(int level, int optname, const void *optval, socklen_t optlen) fails.
		 *
		 *  Most commonly when this exception is thrown an internal runtime X-VR2 library
		 *  call to the OS-specific call to setsockopt has failed, this can be due to a
		 *  portability problem or a library BUG. */
		class SocketOptionParamFailure:public SocketOptionException {
			protected:
				int _optname;
			public:
				/** Default constructor. */
				SocketOptionParamFailure();
				/** This constructor initializes the internal os_errval variable only. */
				SocketOptionParamFailure(OSErrorCodeT x_errno);
				/** This constructor initializes the internal os_errval and optionname variable.
				 *
				 *  Since this constructor properly initilizes the os_errval and the affected
				 *  optionname variable you are encouraged to always use it. */
				SocketOptionParamFailure(OSErrorCodeT x_errno, int __optname);
				int optionNameVal();
				String optionName();
		};

		/** \class SocketOptionIsInvalid SocketOptionIsInvalid.h <xvr2/Net/SocketOptionIsInvalid.h>
		 *  This exception is thrown whenever a call to void Socket::getsockopt(int level, int optname, void *optval, socklen_t *optlen) or 
		 *  void Socket::setsockopt(int level, int optname, const void *optval, socklen_t optlen) fails
		 *  due to a wrong or unavailable option specified, it could be possible that the host
		 *  operating system does not support the given option at all. */
		class SocketOptionIsInvalid:public SocketOptionParamFailure {
			public:
				/** Default constructor. */
				SocketOptionIsInvalid();
				/** This constructor initializes the internal os_errval and optioname variable.
				 *
				 *  Since this constructor properly initilizes the os_errval and the affected
				 *  optionname variable you are encouraged to always use it. */
				SocketOptionIsInvalid(OSErrorCodeT x_errno, int __optname);
		};

		/** \class InvalidSocket InvalidSocket.h <xvr2/Net/InvalidSocket.h>
		 *  Exception thrown whenever the given Socket is not really a socket, however it is
		 *  related to a real and valid file descriptor. */
		class InvalidSocket:public SocketException {
			private:
				int _socket;
			public:
				InvalidSocket();
				InvalidSocket(int _fd);
				int socketID();

		};
	};
};

#endif

