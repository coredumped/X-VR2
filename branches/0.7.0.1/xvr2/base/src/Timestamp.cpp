/*
 * $Id$
 */
#include<xvr2/Timestamp.h>

namespace xvr2{
	Timestamp::Timestamp(UInt32 tstamp){
#if __GNUC__ < 3
		setClassName(_xvr2Timestamp);
#endif
		setTStamp(tstamp);
	}

	Timestamp::Timestamp(const Timestamp *d):Date(d){
#if __GNUC__ < 3
		setClassName(_xvr2Timestamp);
#endif
	}

	Timestamp::Timestamp(const char *f, const char *t){
		//drep = 0;
#if __GNUC__ < 3
		setClassName(_xvr2Timestamp);
#endif
		decode(f, t);
	}

	Timestamp::Timestamp(){
#if __GNUC__ < 3
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

	/*const std::string &Timestamp::toString(){
		return toString();
	}*/
};
