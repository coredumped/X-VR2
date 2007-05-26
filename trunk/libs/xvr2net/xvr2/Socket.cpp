/*
 * $Id$
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

		bool Socket::setDebug(bool enabled){
			bool ret;
			int val;
			socklen_t olen;
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
	};
};

