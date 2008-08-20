/*
 * $Id$
 *
 * X-VR2
 *
 * Copyright (C) Juan V. Guerrero 2007
 *
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
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

	UInt32 operator-(const Timestamp &t1, const Timestamp &t2);
}

#endif
