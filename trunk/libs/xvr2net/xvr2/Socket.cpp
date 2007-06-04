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
#include"Socket.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<cerrno>

namespace xvr2 {
	namespace Net {
		Socket::Socket(){
			_socket = 0;
		}

		Socket::Socket(const Socket &s){
			_socket = s._socket;
		}

		Socket::~Socket(){
		}

		void Socket::close(){
			if(::shutdown(_socket, 2) == -1){
				switch(errno){
					case EBADF:
						throw InvalidFileDescriptor(_socket);
						break;
					case ENOTSOCK:
						throw InvalidSocket(_socket);
						break;
					case ENOTCONN:
						//Lets say you can close it again.
						break;
					default:
						throw NetworkException(errno);
				}
			}
		}

		void Socket::bind(const IPv4Address &ip){
			sockaddr_in name;
			name.sin_family = AF_INET;
			name.sin_addr = *ip.address();
			if(::bind(_socket, (struct sockaddr *)&name, sizeof(sockaddr_in)) != 0){
				switch(errno){
					default:
						NetworkException(errno);
				}
			}
		}

		void Socket::getsockopt(int level, int optname, void *optval, socklen_t *optlen){
			if(::getsockopt(_socket, level, optname, optval, optlen) != 0){
				//Socket option retrieval failure
				switch(errno){
					case EINVAL:
						throw SocketOptionParamFailure(errno, optname);
						break;
					case ENOPROTOOPT:
						throw SocketOptionIsInvalid(errno, optname);
						break;
					default:
						throw SocketOptionException(errno);
				}
			}

		}

		void Socket::setsockopt(int level, int optname, const void *optval, socklen_t optlen){
			if(::setsockopt(_socket, level, optname, optval, optlen) != 0){
				//Socket option set failure
				switch(errno){
					case EINVAL:
						throw SocketOptionParamFailure(errno, optname);
						break;
					case ENOPROTOOPT:
						throw SocketOptionIsInvalid(errno, optname);
						break;
					default:
						throw SocketOptionException(errno);
				}
			}
		}

		bool Socket::debug(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_DEBUG, (void *)&val, &olen);
			if(val == 0){
				ret = false;
			}
			else{
				ret = true;
			}
			return ret;
		}

		bool Socket::debug(bool enabled){
			bool ret;
			int val;
			ret = debug();
			if(enabled == false){
				val = 0;
			}
			else{
				val = 1;
			}
			setsockopt(SOL_SOCKET, SO_DEBUG, (const void *)&val, (socklen_t)sizeof(int));
			return ret;
		}

		bool Socket::reuseAddr(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_REUSEADDR, (void *)&val, &olen);
			if(val == 0){
				ret = false;
			}
			else{
				ret = true;
			}
			return ret;
		}

		bool Socket::reuseAddr(bool enabled){
			bool ret;
			int val;
			ret = reuseAddr();
			if(enabled == false){
				val = 0;
			}
			else{
				val = 1;
			}
			setsockopt(SOL_SOCKET, SO_REUSEADDR, (const void *)&val, (socklen_t)sizeof(int));
			return ret;
		}

		bool Socket::keepalive(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_KEEPALIVE, (void *)&val, &olen);
			if(val == 0){
				ret = false;
			}
			else{
				ret = true;
			}
			return ret;
		}

		bool Socket::keepalive(bool enabled){
			bool ret;
			int val;
			ret = keepalive();
			if(enabled == false){
				val = 0;
			}
			else{
				val = 1;
			}
			setsockopt(SOL_SOCKET, SO_KEEPALIVE, (const void *)&val, (socklen_t)sizeof(int));
			return ret;
		}

		bool Socket::dontroute(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_DONTROUTE, (void *)&val, &olen);
			if(val == 0){
				ret = false;
			}
			else{
				ret = true;
			}
			return ret;
		}

		bool Socket::dontroute(bool enabled){
			bool ret;
			int val;
			ret = dontroute();
			if(enabled == false){
				val = 0;
			}
			else{
				val = 1;
			}
			setsockopt(SOL_SOCKET, SO_DONTROUTE, (const void *)&val, (socklen_t)sizeof(int));
			return ret;
		}

		void Socket::linger(bool enabled, int secs){
			struct linger val;
			if(enabled == false){
				val.l_onoff = 0;
			}
			else{
				val.l_onoff = 1;
				val.l_linger = secs;
			}
			setsockopt(SOL_SOCKET, SO_DONTROUTE, (const void *)&val, (socklen_t)sizeof(struct linger));
		}

		int Socket::linger(){
			struct linger val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_DONTROUTE, (void *)&val, &olen);
			if(val.l_onoff == 1){
				return val.l_linger;
			}
			return 0;
		}

		bool Socket::broadcast(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_BROADCAST, (void *)&val, &olen);
			if(val == 0){
				ret = false;
			}
			else{
				ret = true;
			}
			return ret;
		}

		bool Socket::broadcast(bool enabled){
			bool ret;
			int val;
			ret = broadcast();
			if(enabled == false){
				val = 0;
			}
			else{
				val = 1;
			}
			setsockopt(SOL_SOCKET, SO_BROADCAST, (const void *)&val, (socklen_t)sizeof(int));
			return ret;
		}

		bool Socket::recvOOBInline(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_BROADCAST, (void *)&val, &olen);
			if(val == 0){
				ret = false;
			}
			else{
				ret = true;
			}
			return ret;
		}

		bool Socket::recvOOBInline(bool enabled){
			bool ret;
			int val;
			ret = recvOOBInline();
			if(enabled == false){
				val = 0;
			}
			else{
				val = 1;
			}
			setsockopt(SOL_SOCKET, SO_BROADCAST, (const void *)&val, (socklen_t)sizeof(int));
			return ret;
		}

		int Socket::sendBufSize(){
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_SNDBUF, (void *)&val, &olen);
			return val;
		}

		int Socket::sendBufSize(int newsize){
			int ret;
			ret = sendBufSize();
			setsockopt(SOL_SOCKET, SO_SNDBUF, (const void *)&newsize, (socklen_t)sizeof(int));
			return ret;
		}

		int Socket::recvBufSize(){
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_RCVBUF, (void *)&val, &olen);
			return val;
		}

		int Socket::recvBufSize(int newsize){
			int ret;
			ret = recvBufSize();
			setsockopt(SOL_SOCKET, SO_RCVBUF, (const void *)&newsize, (socklen_t)sizeof(int));
			return ret;
		}

		bool Socket::isStream(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_TYPE, (void *)&val, &olen);
			if(val == SOCK_STREAM){
				ret = true;
			}
			else{
				ret = false;
			}
			return ret;
		}

		bool Socket::isDatagram(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_TYPE, (void *)&val, &olen);
			if(val == SOCK_DGRAM){
				ret = true;
			}
			else{
				ret = false;
			}
			return ret;
		}

		bool Socket::isRaw(){
			bool ret;
			int val;
			socklen_t olen;
			getsockopt(SOL_SOCKET, SO_TYPE, (void *)&val, &olen);
			if(val == SOCK_RAW){
				ret = true;
			}
			else{
				ret = false;
			}
			return ret;
		}

		bool Socket::isIPv4(){
			return is_ipv4;
		}

		bool Socket::isIPv6(){
			return (is_ipv4==true)?false:true;
		}
	};
};

