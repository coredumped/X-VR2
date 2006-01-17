/*
 * $Id$
 */
#include<xvr2/Exception.h>
#include<xvr2/NetworkException.h>

#ifndef __xvr2_NoIPForYouException_H__
#define __xvr2_NoIPForYouException_H__

namespace xvr2 {
	namespace Exception{
		/**
		 * \class NoIPForYou
		 * \version $Revision$
		 * \brief The requested name is valid but does not have an IP address. */
		class NoIPForYou:public Network{
			public:
				/**
				 * Default constructor
				 */
				NoIPForYou();
		};

	};
};

#endif

