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

	Time::Time(const char *time_text):Date("%T", time_text){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time::Time(const String &time_text):Date("%T", time_text){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Time);
#endif
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

	Time::Time(const Time *t):Date(t){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Time);
#endif
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
	
	const String *Time::toString(){
		if(drep == 0){
			drep = new String();
		}
		if(hour <= 9)
			drep->concat(0);
		drep->concat(hour);
		drep->concat(":");
		if(minute <= 9)
			drep->concat(0);
		drep->concat(minute);
		drep->concat(":");
		if(second <= 9)
			drep->concat(0);
		drep->concat(second);
		return drep;
	}
};

