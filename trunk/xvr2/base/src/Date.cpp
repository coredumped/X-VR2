/*
 * $Id$
 */
#ifdef GCC_2_96
#define _XOPEN_SOURCE
#endif
#include<xvr2/Date.h>
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
		drep = 0;
		getCurrentTime();
	}

	Date::Date(const Date *d){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Date);
#endif
		drep = 0;
		minute = d->minute;
		second = d->second;
		hour = d->hour;
		dayofweek = d->dayofweek;
		dayofyear = d->dayofyear;
		dayofmonth = d->dayofmonth;
		month = d->month;
		year = d->year;
		unixtime = d->unixtime;
	}

	Date::Date(int __y, int __m, int __dw, int __dm, int __h, int __mi, int __s){
		struct tm t;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Date);
#endif
		drep = 0;
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
		drep = 0;
		setTStamp(__unixtime);
	}

	void Date::decode(const char *format, const char *date_text){
		struct tm *t = 0;
		t = new tm();
		if(strptime(date_text, format, t) == NULL){
			xvr2_delete(t);
			throw Exception::DateParse();
		}
		hour = t->tm_hour;
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
		minute = t->tm_min;
		second = t->tm_sec;
		dayofweek = t->tm_wday;
		dayofyear = t->tm_yday;
		dayofmonth = t->tm_mday;
		month = t->tm_mon + 1;
		if(t->tm_year < 1900){
			year = t->tm_year + 1900;
		}
		else{
			year = t->tm_year;
		}
		unixtime = mktime(t);
		xvr2_delete(t);
	}

	Date::Date(const char *format, const char *date_text){
		drep = 0;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Date);
#endif
		decode(format, date_text);
	}

	Date::Date(const String &format, const String &date_text){
		struct tm t;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Date);
#endif
		drep = 0;
		if(strptime(date_text.toCharPtr(), format.toCharPtr(), &t) == NULL)
			throw Exception::DateParse();
		hour = t.tm_hour;
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
		minute = t.tm_min;
		second = t.tm_sec;
		dayofweek = t.tm_wday;
		dayofyear = t.tm_yday;
		dayofmonth = t.tm_mday;
		month = t.tm_mon;
		if(t.tm_year < 1900){
			year = t.tm_year + 1900;
		}
		else{
			year = t.tm_year;
		}
		unixtime = mktime(&t);
	}

	Date::~Date(){
		if(drep != 0)
			xvr2_delete(drep);
	}

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

	const String *Date::toString(){
		if(drep == 0){
			drep = new String(year);
		}
		drep->assign(year);
		drep->concat("-");
		if(month <= 9)
			drep->concat(0);
		drep->concat(month);
		drep->concat("-");
		if(dayofmonth <= 9)
			drep->concat(0);
		drep->concat(dayofmonth);
		drep->concat(" ");
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

	void Date::add(DateARITHParts component, int value){
		int fsec;
		switch(component){
			case DAYS:
				fsec = value * 86400;
				break;
			case HOURS:
				fsec = value * 3600;
				break;
			case MINUTES:
				fsec = value * 60;
				break;
			default:
				fsec = value;
		}
		setTStamp(unixtime + fsec);
	}
};

