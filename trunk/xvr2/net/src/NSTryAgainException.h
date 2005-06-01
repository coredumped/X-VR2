/*
 * $Id$
 */
#include<xvr2/Exception.h>
#include<xvr2/NetworkException.h>
#ifndef __xvr2_NSTryAgainException_H__
#define __xvr2_NSTryAgainException_H__

namespace xvr2 {
	namespace Exception{
		/**
		 * \class NSTryAgain
		 * \version $Revision$
		 * \brief A temporary error occurred on an authoritative name server.  Try */
		class NSTryAgain:public Network{
			public:
				/**
				 * Default constructor
				 */
				NSTryAgain();
		};

	};
};

#endif

