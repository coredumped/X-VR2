/*
 * $Id$
 */
#include"config.h"
#include "Time.h"
#include<sstream>

namespace xvr2{

	void Time::encode(){
		/*if(string_representation != 0){
			delete string_representation;
		}*/
		std::stringstream stream;
		if(hour <= 9)
			stream << "0";
		stream << hour << ":";
		if(minute <= 9)
			stream << "0";
		stream << minute << ":";
		if(second <= 9)
			stream << "0";
		stream << second;
		string_representation = stream.str();
	}
	Time::Time(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time::~Time(){
	}

	Time::Time(UInt32 tstamp){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Time);
#endif
		setTStamp(tstamp);
	}

	Time::Time(const char *time_text):Date("%T", time_text){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time::Time(const String &time_text):Date("%T", time_text){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	const UInt32 Time::timestamp(){
		return unixTime();
	}

	Time::Time(int __hour, int __min, int __sec){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Time);
#endif
		hour      = __hour;
		minute    = __min;
		second    = __sec;
		dayofweek = 0;
		dayofyear = 0;
		month     = 0;
		year      = 0;
		encode();
	}

	Time::Time(const Time *t):Date(t){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time::Time(const Time &t):Date(t){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time &Time::operator=(const Time &t){
		setTStamp(t.unixtime);
		return *this;
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

	/*const String &Time::toString() const{
		//return drep;
		return *string_representation;
	}*/
};
