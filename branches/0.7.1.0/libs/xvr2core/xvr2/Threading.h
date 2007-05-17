/*
 * $Id$
 */
#ifndef __XVR2_THREADING_H__
#define __XVR2_THREADING_H__
#include<xvr2/System.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	/**
	 * This class is an interface for all Threading classes
	 */
	class Threading:public System{
		public:
			/** Default Constructor, remember that this class
			 * is just an interface */
			Threading();
			/**
			 * Please use this set of constants to define or
			 * stablish a thread execution policy
			 */
			enum SchedPolicy{
				/** Default scheduling policy, 
				 *  non-realtime */
				NORMAL,
				/** Round Robin based realtime 
				 *  scheduling policy */
				ROUND_ROBIN,
				/** First In First Out based realtime 
				 *  scheduling policy */
				FIFO
			};
	};
}

#endif

