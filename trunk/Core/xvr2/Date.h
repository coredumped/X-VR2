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
#ifndef __XVR2_DATE_H__
#define __XVR2_DATE_H__
#include<xvr2/System.h>
#include<sys/types.h>
#include<xvr2/String.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	
	/**
	 * This class implements the basic date/time handling facilities
	 */
	class Date:public System{
		protected:
			/** This variable stores the time queried by getCurrentTime(); */
			time_t unixtime;
			/** This member holds the String representation of the 
			 *  current Date */
			//String drep;
			void setTStamp(UInt32 tstamp);
			void decode(const char *format, const char *date_text);
			virtual void encode();
			std::string *string_representation;
		public:
			enum DateAMPM{
				AM,
				PM
			};
			enum DateARITHParts{
				DAYS,
				HOURS,
				MINUTES,
				SECONDS
			};
			/** This member stores the hour 0-23*/
			int hour;
			/** This member will show the hour using non-24hr format */
			int hr12hour;
			/** This member stores the minute 0-59*/
			int minute;
			/** This member stores the second 0-59*/
			int second;
			/** This member stores the day of the week e.g Monday, Tuesday, Wednesday... */
			int dayofweek;
			/** This member stores the days elapsed since january first of the current year  */
			int dayofyear;
			/** This member stores the day of the month 1-31*/
			int dayofmonth;
			/** This member stores the month 1-12*/
			int month;
			/** This member stores the year 1960 - ???? */
			int year;
			/** This member <i>knows</i> whether the timing is AM or PM */
			int hr12ampm;

			/** Default constructor, this will initialize the value of unixtime */
			Date();
			/** This constructor will initialize every member to its
			 *  unixtime equivalent. Unixtime is the number of seconds
			 *  since January 1st 1970 */
			Date(UInt32 __unixtime);
			/** This will initialize every one of this class members
			 *  to the following values:<br>
			 *  year: __y <br>
			 *  month: __m <br>
			 *  day of week: __dw <br>
			 *  day of month: __dm <br>
			 *  hour: __h <br>
			 *  minute: __mi <br>
			 *  second: __s */
			Date(int __y, int __m, int __dw, int __dm, int __h, int __mi, int __s = 0);
			/** By calling this constructor you'll be able to initialize a
			 *  Date object from a string with the specified format.
			 *  This method makes use of the strptime(3) C function, for
			 *  more information on the format string read the manpage for
			 *  strptime.
			 *  \param format The format as a valid strptime format string
			 *  \param date_text The date as a string matching the given 
			 *  format */
			Date(const char *format, const char *date_text);
			/** By calling this constructor you'll be able to initialize a
			 *  Date object from a string with the specified format.
			 *  This method makes use of the strptime(3) C function, for
			 *  more information on the format string read the manpage for
			 *  strptime.
			 *  \param format The format as a valid strptime format string
			 *  \param date_text The date as a string matching the given 
			 *  format */
			Date(const String &format, const String &date_text);
			Date(const Date &d);
			Date(const Date *d);
			virtual ~Date();
			Date &operator=(const Date &_d);
			/** This method will update the value of unixtime and all the other <i>broken-time</i> values */
			virtual time_t getCurrentTime();
			
			/** This methid will give you the numeric representation of
			 *  the date in the unix time format */
			const UInt32 unixTime();
			const UInt32 unixTime() const;
			/**
			 * This will convert the current date object to the following
			 * format:   YYYY-MM-DD HH:MM:SS
			 */
			virtual std::string toString();
			virtual void add(DateARITHParts component, int value);
			static Date Now();
	};

};


#endif
