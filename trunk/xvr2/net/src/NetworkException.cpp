/*
 * $Id$
 */
#include<xvr2/NetworkException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Network::Network(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NetworkException);
#endif
#ifndef strerror
			description = (char *)xvr2::excepGenNet;
#else
			description = strerror(errno);
#endif
		}

		ConnectionTimeout::ConnectionTimeout(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ConnectionTimeoutException);
#endif
			description = (char *)xvr2::excepNetTimeout;
		}

		ConnectionRefused::ConnectionRefused(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ConnectionRefusedException);
#endif
			description = (char *)xvr2::excepNetRefused;
		}

		NetworkUnreachable::NetworkUnreachable(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NetworkUnreachableException);
#endif
			description = (char *)xvr2::excepNetUnreach;
		}

		SocketAlreadyBounded::SocketAlreadyBounded(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SocketAlreadyBoundedException);
#endif
			description = (char *)xvr2::excepSockUsed;
		}

		SocketAlreadyUsed::SocketAlreadyUsed(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SocketAlreadyUsedException);
#endif
			description = (char *)xvr2::excepSockListening;
		}
	};
};

