/*
 * $Id$
 */

#include<Exception.h>
#include<NetworkException.h>
#ifndef __xvr2_HostNotFoundException_H__
#define __xvr2_HostNotFoundException_H__

namespace xvr2 {
	namespace Exception{
		/**
		 * \class HostNotFound HostNotFoundException.h
		 * \version $Revision$
		 * \brief Unable to find the specified host please check your /etc/hosts file or your DNS client config 
		 */
		class HostNotFound:public Network{
			public:
				/**
				 * Default constructor
				 */
				HostNotFound();
		};
	};
};

#endif

