/*
 * $Id$
 */
#include<Time.h>

namespace xvr2{

	Time::Time(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time::Time(UInt32 tstamp){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Time);
#endif
		setTStamp(tstamp);
	}

	const UInt32 Time::timestamp(){
		return unixTime();
	}

	Time::Time(int __hour, int __min, int __sec){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Time);
#endif
		hour      = __hour;
		minute    = __min;
		second    = __sec;
		dayofweek = 0;
		dayofyear = 0;
		month     = 0;
		year      = 0;
	}

	int Time::Hour(){
		getCurrentTime();
		return hour;
	}

	int Time::Minute(){
		getCurrentTime();
		return minute;
	}

	int Time::Second(){
		getCurrentTime();
		return second;
	}
	
	const String &Time::toString(){
		drep.deleteString();
		drep = Hour();
		drep += ":";
		drep = Minute();
		drep += ":";
		drep = Second();
		return drep;
	}
};

