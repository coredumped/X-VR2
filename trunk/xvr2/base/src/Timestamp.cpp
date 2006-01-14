/*
 * $Id$
 */
#include<xvr2/Timestamp.h>

namespace xvr2{
	Timestamp::Timestamp(UInt32 tstamp){
#ifndef USING_GCC3
		setClassName(_xvr2Timestamp);
#endif
		setTStamp(tstamp);
	}

	Timestamp::Timestamp(const Timestamp *d):Time(d){
#ifndef USING_GCC3
		setClassName(_xvr2Timestamp);
#endif
	}

	Timestamp::Timestamp(const char *f, const char *t){
		drep = 0;
#ifndef USING_GCC3
		setClassName(_xvr2Timestamp);
#endif
		decode(f, t);
	}

	Timestamp::Timestamp(){
#ifndef USING_GCC3
		setClassName(_xvr2Timestamp);
#endif
		getCurrentTime();
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

	const std::string &Timestamp::toString(){
		/*if(drep == 0)
			drep = new String((unsigned int)unixtime);
		else
			drep->assign((unsigned int)unixtime);*/
		return Date::toString();
	}
};
