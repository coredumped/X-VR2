/*
 * $Id$
 */
#ifndef __XVR2_TIMESTAMP_H__
#define __XVR2_TIMESTAMP_H__

#include<Time.h>

namespace xvr2{

	/**
	 * This class implements the Timestamp functionality, it will store
	 * the timestamp the first time it is instanciated
	 */
	class Timestamp:public Time{
		public:
			Timestamp();
			Timestamp(UInt32 tstamp);
			/** Returns the current hour */
			int Hour();
			/** Returns the current minute */
			int Minute();
			/** Returns the current second */
			int Second();
			/** Returns the current timestamp as unix time */
			UInt32 timestamp();
	};
};

#endif
