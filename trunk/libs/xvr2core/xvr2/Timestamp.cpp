/*
 * $Id$
 */
#include"config.h"
#include "Timestamp.h"

namespace xvr2{
	Timestamp::Timestamp(UInt32 tstamp){
		string_representation = 0;
		setTStamp(tstamp);
	}

	Timestamp::Timestamp(const Timestamp *d):Date(d){
	}

	Timestamp::Timestamp(const Timestamp &d){
		string_representation = 0;
		setTStamp(d.unixtime);
	}

	Timestamp::Timestamp(const char *f, const char *t){
		decode(f, t);
	}

	Timestamp::Timestamp(){
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
