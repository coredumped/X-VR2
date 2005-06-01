/*
 * $Id$
 */
#include<xvr2/Exception.h>
#include<xvr2/NetworkException.h>
#ifndef __xvr2_ConnectionResetByPeerException_H__
#define __xvr2_ConnectionResetByPeerException_H__

namespace xvr2 {
	namespace Exception{
		/**
		 * \class ConnectionResetByPeer
		 * \version $Revision$
		 * \brief The current connection suffered a reset from the peer
		 */
		class ConnectionResetByPeer:public Network{
			public:
				/**
				 * Default constructor
				 */
				ConnectionResetByPeer();
		};

	};
};


#endif

