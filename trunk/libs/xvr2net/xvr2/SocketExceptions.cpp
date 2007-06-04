/*
 * $Id$
 */
#include"SocketExceptions.h"
#include<sys/socket.h>
#define _XOPEN_SOURCE 600
#include <string.h>


#ifndef SOCKET_ERROR_STRING_MAX_CHARS
#define SOCKET_ERROR_STRING_MAX_CHARS 512
#endif

namespace xvr2 {
	namespace Net {
		static const char *_sckt_gen_desc = "Undetermined socket-level exception received.";
		static const char *_sckt_option_desc = "Unable to set/get socket option value.";
		static const char *_sckt_option_p_desc = "Unable to set socket level option value, parameter specification failed.";
		static const char *_sckt_option_i_desc = "Unable to get/set socket level option value, specific option is not available at the given level.";
		SocketException::SocketException(){
			description = (char *)_sckt_gen_desc;
		}
		SocketException::SocketException(OSErrorCodeT error_code):NetworkException(error_code){
			description = (char *)_sckt_gen_desc;
		}

		SocketOptionException::SocketOptionException(){
			description = (char *)_sckt_option_desc;
		}

		SocketOptionException::SocketOptionException(OSErrorCodeT x_errno):SocketException(x_errno){
			description = (char *)_sckt_option_desc;
		}

		SocketOptionParamFailure::SocketOptionParamFailure():SocketOptionException(){
			description = (char *)_sckt_option_p_desc;
		}

		SocketOptionParamFailure::SocketOptionParamFailure(OSErrorCodeT x_errno):SocketOptionException(x_errno){
			description = (char *)_sckt_option_p_desc;
		}

		SocketOptionParamFailure::SocketOptionParamFailure(OSErrorCodeT x_errno, int __optname):SocketOptionException(x_errno){
			description = (char *)_sckt_option_p_desc;
			_optname = __optname;
		}

		int SocketOptionParamFailure::optionNameVal(){
			return _optname;
		}

		String SocketOptionParamFailure::optionName(){
			switch(_optname){
				case SO_DEBUG:
					return String("SO_DEBUG");
					break;
				case SO_REUSEADDR:
					return String("SO_REUSEADDR");
					break;
				case SO_TYPE:
					return String("SO_TYPE");
					break;
				case SO_ERROR:
					return String("SO_ERROR");
					break;
				case SO_DONTROUTE:
					return String("SO_DONTROUTE");
					break;
				case SO_BROADCAST:
					return String("SO_BROADCAST");
					break;
				case SO_SNDBUF:
					return String("SO_SNDBUF");
					break;
				case SO_RCVBUF:
					return String("SO_RCVBUF");
					break;
				case SO_SNDBUFFORCE:
					return String("SO_SNDBUFFORCE");
					break;
				case SO_RCVBUFFORCE:
					return String("SO_RCVBUFFORCE");
					break;
				case SO_KEEPALIVE:
					return String("SO_KEEPALIVE");
					break;
				case SO_OOBINLINE:
					return String("SO_OOBINLINE");
					break;
				case SO_NO_CHECK:
					return String("SO_NO_CHECK");
					break;
				case SO_PRIORITY:
					return String("SO_PRIORITY");
					break;
				case SO_LINGER:
					return String("SO_LINGER");
					break;
				case SO_BSDCOMPAT:
					return String("SO_BSDCOMPAT");
					break;
				case SO_PASSCRED:
					return String("SO_PASSCRED");
					break;
				case SO_PEERCRED:
					return String("SO_PEERCRED");
					break;
				case SO_RCVLOWAT:
					return String("SO_RCVLOWAT");
					break;
				case SO_SNDLOWAT:
					return String("SO_SNDLOWAT");
					break;
				case SO_RCVTIMEO:
					return String("SO_RCVTIMEO");
					break;
				case SO_SNDTIMEO:
					return String("SO_SNDTIMEO");
					break;
			}
			return String("Unknown");
		}

		SocketOptionIsInvalid::SocketOptionIsInvalid():SocketOptionParamFailure(){
			description = (char *)_sckt_option_i_desc;
		}

		SocketOptionIsInvalid::SocketOptionIsInvalid(OSErrorCodeT x_errno, int __optname):SocketOptionParamFailure(x_errno, __optname){
			description = (char *)_sckt_option_i_desc;
		}

	}
};

