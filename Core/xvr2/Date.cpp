/*
 * $Id$
 *
 * X-VR2
 *
 * Copyright (C) Juan V. Guerrero 2007
 *
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#include"config.h"
#if __GNUC__ <= 2
#define _XOPEN_SOURCE
#endif
#include"Date.h"
#include<time.h>
#include<sstream>

namespace xvr2{

	void Date::encode(){
		if(string_representation != 0){
			delete string_representation;
		}
		std::stringstream stream;
		stream << year << "-";
		if(month <= 9)
			stream << "0";
		stream << month << "-";
		if(dayofmonth <= 9)
			stream << "0";
		stream << dayofmonth << " ";
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
		encode();
	}

	Date::Date(){
		//drep = 0;
		string_representation = 0;
		getCurrentTime();
	}

	Date::Date(const Date *d){
		string_representation = 0;
		//drep = 0;
		minute = d->minute;
		second = d->second;
		hour = d->hour;
		dayofweek = d->dayofweek;
		dayofyear = d->dayofyear;
		dayofmonth = d->dayofmonth;
		month = d->month;
		year = d->year;
		unixtime = d->unixtime;

		encode();
	}

	Date::Date(int __y, int __m, int __dw, int __dm, int __h, int __mi, int __s){
		struct tm t;
		string_representation = 0;
		//drep = 0;
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
		encode();
	}

	Date::Date(UInt32 __unixtime){
		string_representation = 0;
		//drep = 0;
		setTStamp(__unixtime);
	}

	Date::Date(const Date &_d){
		string_representation = 0;
		//drep = 0;
		setTStamp(_d.unixtime);
	}

	Date &Date::operator=(const Date &_d){
		string_representation = 0;
		setTStamp(_d.unixtime);
		return *this;
	}

	void Date::decode(const char *format, const char *date_text){
		struct tm *t = 0;
		t = new tm();
		if(strptime(date_text, format, t) == NULL){
			xvr2_delete(t);
			throw DateParseException();
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
		encode();
	}

	Date::Date(const char *format, const char *date_text){
		string_representation = 0;
		decode(format, date_text);
		encode();
	}

	Date::Date(const String &format, const String &date_text){
		string_representation = 0;
		decode(format.toCharPtr(), date_text.toCharPtr());
		encode();
	}

	Date::~Date(){
		if(string_representation != 0){
			delete string_representation;
			string_representation = 0;
		}
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
		encode();
		return unixtime;
	}

	const UInt32 Date::unixTime(){
		return unixtime;
	}

	const UInt32 Date::unixTime() const{
		return unixtime;
	}

	std::string Date::toString(){
		//return drep.toString();
		//return *string_representation;
		return std::string(string_representation->c_str());
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

	Date Date::Now(){
		return Date();
	}

	Date operator+(const Date &d, UInt32 secs){
		return Date(d.unixTime() + secs);
	}

	Date operator-(const Date &d, UInt32 secs){
		return Date(d.unixTime() - secs);
	}

	UInt32 operator+(UInt32 secs, const Date &d){
		return secs + d.unixTime();
	}

}

