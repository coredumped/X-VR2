/*
 * $Id$
 *
 *                 Juan V. Guerrero <coredumped@esolutions4all.com>
 */
#include<Date.h>
#include<time.h>

namespace xvr2{

	void Date::setTStamp(UInt32 tstamp){
		struct tm t;
		unixtime = tstamp;
		localtime_r(&unixtime, &t);
		hour       = t.tm_hour;
		if(hour > 12){
			hr12hour = hour - 12;
			hr12ampm = Date::PM;
		}
		else{
			if(hour == 0){
				hr12hour = 12;
			}
			else{
				hr12hour = hour;
			}
			hr12ampm = Date::AM;
		}
		minute     = t.tm_min;
		second     = t.tm_sec;
		dayofweek  = t.tm_wday + 1;
		dayofmonth = t.tm_mday;
		month      = t.tm_mon + 1;
		year       = t.tm_year + 1900;
	}

	Date::Date(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Date);
#endif
		getCurrentTime();
	}

	Date::Date(int __y, int __m, int __dw, int __dm, int __h, int __mi, int __s){
		struct tm t;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Date);
#endif
		hour       = __h;
		if(hour > 12){
			hr12hour = hour - 12;
			hr12ampm = Date::PM;
		}
		else{
			if(hour == 0){
				hr12hour = 12;
			}
			else{
				hr12hour = hour;
			}
			hr12ampm = Date::AM;
		}
		minute     = __mi;
		second     = __s;
		dayofweek  = __dw;
		dayofmonth = __dm;
		month      = __m;
		year       = __y;

		t.tm_hour = hour;
		t.tm_min = minute;
		t.tm_sec = second;
		t.tm_wday = dayofweek;
		t.tm_mday = dayofmonth;
		t.tm_mon = month;
		t.tm_year = year;

		unixtime = mktime(&t);
	}

	Date::Date(UInt32 __unixtime){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Date);
#endif
		setTStamp(__unixtime);
	}

	Date::~Date(){;}

	time_t Date::getCurrentTime(){
		struct tm t;
		time(&unixtime);
		localtime_r(&unixtime, &t);
		hour       = t.tm_hour;
		if(hour > 12){
			hr12hour = hour - 12;
			hr12ampm = Date::PM;
		}
		else{
			if(hour == 0){
				hr12hour = 12;
			}
			else{
				hr12hour = hour;
			}
			hr12ampm = Date::AM;
		}
		minute     = t.tm_min;
		second     = t.tm_sec;
		dayofweek  = t.tm_wday + 1;
		dayofmonth = t.tm_mday;
		month      = t.tm_mon + 1;
		year       = t.tm_year + 1900;
		return unixtime;
	}

	const UInt32 Date::unixTime(){
		return unixtime;
	}

	const String &Date::toString(){
		drep.deleteString();
		drep = year;
		drep += "-";
		if(month <= 9)
			drep += "0";
		drep += month;
		drep += "-";
		if(dayofmonth <= 9)
			drep += "0";
		drep += dayofmonth;
		drep += " ";
		if(hour <= 9)
			drep += "0";
		drep += hour;
		drep += ":";
		if(minute <= 9)
			drep += "0";
		drep += minute;
		drep += ":";
		if(second <= 9)
			drep += "0";
		drep += second;
		return drep;
	}
};

