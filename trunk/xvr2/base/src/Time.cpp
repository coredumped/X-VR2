/*
 * $Id$
 */
#include<xvr2/Time.h>
#include<sstream>

namespace xvr2{

	void Time::encode(){
		/*if(hour <= 9)
			drep.concat(0);
		drep.concat(hour);
		drep.concat(":");
		if(minute <= 9)
			drep.concat(0);
		drep.concat(minute);
		drep.concat(":");
		if(second <= 9)
			drep.concat(0);
		drep.concat(second);*/
		if(string_representation != 0){
			delete string_representation;
		}
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
		string_representation = new std::string(stream.str());
	}
	Time::Time(){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time::Time(UInt32 tstamp){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Time);
#endif
		setTStamp(tstamp);
	}

	Time::Time(const char *time_text):Date("%T", time_text){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	Time::Time(const String &time_text):Date("%T", time_text){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Time);
#endif
	}

	const UInt32 Time::timestamp(){
		return unixTime();
	}

	Time::Time(int __hour, int __min, int __sec){
#if GCC_MAJOR_VERSION < 3
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
#if GCC_MAJOR_VERSION < 3
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
	
	/*const String &Time::toString() const{
		//return drep;
		return *string_representation;
	}*/
};
