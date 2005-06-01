/*
 * $Id$
 */
#include<xvr2/ConnectionResetByPeerException.h>
#include<xvr2/MessageStrings.h>

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

