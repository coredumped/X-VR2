/*
 * $Id$
 */
#include"config.h"
#include "Timestamp.h"

namespace xvr2{
	Timestamp::Timestamp(UInt32 tstamp){
#if __GNUC__ < 3
		setClassName(_xvr2Timestamp);
#endif
		//string_representation = 0;
		setTStamp(tstamp);
	}

	Timestamp::Timestamp(const Timestamp *d):Date(d){
#if __GNUC__ < 3
		setClassName(_xvr2Timestamp);
#endif
	}

	Timestamp::Timestamp(const Timestamp &d){
#if __GNUC__ < 3
		setClassName(_xvr2Timestamp);
#endif
		//string_representation = 0;
		setTStamp(d.unixtime);
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

	Timestamp::~Timestamp(){
	}

	Timestamp &Timestamp::operator=(const Timestamp &t){
		setTStamp(t.unixtime);
		return *this;
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
