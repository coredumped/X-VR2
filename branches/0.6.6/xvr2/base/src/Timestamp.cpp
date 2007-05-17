/*
 * $Id$
 */
#include<Timestamp.h>

namespace xvr2{
	Timestamp::Timestamp(UInt32 tstamp){
#ifndef USING_GCC3
		setClassName(_xvr2Timestamp);
#endif
		setTStamp(tstamp);
	}

	Timestamp::Timestamp(){
		getCurrentTime();
#ifndef USING_GCC3
		setClassName(_xvr2Timestamp);
#endif
	}

	int Timestamp::Hour(){
		return hour;
	}

	int Timestamp::Minute(){
		return minute;
	}

	int Timestamp::Second(){
		return second;
	}

	UInt32 Timestamp::timestamp(){
		return unixtime;
	}
};
