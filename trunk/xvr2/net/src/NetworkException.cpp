/*
 * $Id$
 */
#include<xvr2/NetworkException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Network::Network(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2NetworkException);
#endif
#ifndef strerror
			description = (char *)xvr2::excepGenNet;
#else
			description = strerror(errno);
#endif
		}

		ConnectionTimeout::ConnectionTimeout(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ConnectionTimeoutException);
#endif
			description = (char *)xvr2::excepNetTimeout;
		}

		ConnectionRefused::ConnectionRefused(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ConnectionRefusedException);
#endif
			description = (char *)xvr2::excepNetRefused;
		}

		NetworkUnreachable::NetworkUnreachable(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2NetworkUnreachableException);
#endif
			description = (char *)xvr2::excepNetUnreach;
		}

		SocketAlreadyBounded::SocketAlreadyBounded(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2SocketAlreadyBoundedException);
#endif
			description = (char *)xvr2::excepSockUsed;
		}

		SocketAlreadyUsed::SocketAlreadyUsed(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2SocketAlreadyUsedException);
#endif
			description = (char *)xvr2::excepSockListening;
		}


	};
};

