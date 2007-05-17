/*
 * $Id$
 */
#include<ConnectionResetByPeerException.h>
#include<MessageStrings.h>

namespace xvr2{
	namespace Exception{

		ConnectionResetByPeer::ConnectionResetByPeer(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ConnectionResetByPeerException);
#endif
			description = (char *)xvr2::excepConnectionResetByPeer;
		}

	};
};

