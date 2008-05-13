/*
 * $Id$
 */
#ifndef __XVR2_TIMESTAMP_H__
#define __XVR2_TIMESTAMP_H__

#include<xvr2/Time.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{

	/**
	 * This class implements the Timestamp functionality, it will store
	 * the timestamp the first time it is instanciated
	 */
	class Timestamp:public Date{
		public:
			Timestamp();
			Timestamp(const Timestamp *t);
			Timestamp(const Timestamp &t);
			Timestamp(const char *f, const char *t);
			Timestamp(UInt32 tstamp);
			Timestamp &operator=(const Timestamp &t);
			~Timestamp();
			/** Returns the current hour */
			int Hour();
			/** Returns the current minute */
			int Minute();
			/** Returns the current second */
			int Second();
			/** Returns the current timestamp as unix time */
			UInt32 timestamp();
			//const std::string &toString();
	};
};

#endif
