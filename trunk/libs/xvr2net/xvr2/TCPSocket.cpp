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
#include"TCPSocket.h"
#include<cerrno>

namespace xvr2 {
	namespace Net {

		void TCPSocket::create(int protoid){
			_socket = socket(AF_INET, SOCK_STREAM, protoid);
			if(_socket == -1){
				//Socket creation failed
				switch(errno){
					case EPROTONOSUPPORT:
						throw UnsupportedProtocol(errno, protoid);
						break;
					case EACCES:
						break;
					case ENOBUFS:
						break;
					case EMFILE:
					case ENFILE:
					default:
						throw NetworkException(errno);
				}
			}
		}

		TCPSocket::TCPSocket(){
			create();
		}

		TCPSocket::TCPSocket(const IPv4Address &addr, int port){
			create();
			connect(addr, port);
		}

		TCPSocket::TCPSocket(const TCPSocket &s){
			_socket = s._socket;
		}

		TCPSocket::TCPSocket(int fd){
			_socket = fd;
		}

		TCPSocket::~TCPSocket(){
		}

		void TCPSocket::connect(const IPv4Address &addr, int port){
			struct sockaddr_in name;
			if(_socket == -1) create();
			name.sin_family = AF_INET;
			name.sin_port = htons(port);
			name.sin_addr = *addr.address();
			if(::connect(_socket, (struct sockaddr *)&name, sizeof(name)) != 0){
				int erx = errno;
				close();
				_socket = -1;
				switch(erx){
					case ETIMEDOUT:
						throw ConnectionTimeout();
						break;
					case ECONNREFUSED:
						throw ConnectionRefused();
						break;
					case ENETUNREACH:
						throw NetworkUnreachable();
						break;
					default:
						throw NetworkException(erx);
				}
			}
			in.open(_socket);
			out.open(_socket);
		}
	};
};

