/*
 * $Id$
 */
#ifndef __XVR2_TIME_H__
#define __XVR2_TIME_H__
#include<xvr2/Date.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{

	/**
	 * This class represents the time object
	 */
	class Time:public Date{
		protected:
			virtual void encode();
		public:
			/** Default constructor, it does nothing */
			Time();
			/** This will initialize all internal variables to the
			 *  timestamp <b>tstamp</b> */	 
			Time(UInt32 tstamp);
			/** This will initialize the internal values to the corresponding
			 * <b>hour, min</b> and <b>sec</b>. */
			Time(int hour, int min, int sec);
			/** This constructor will attempt to convert the time given as
			 *  a string in the format HH:MM:SS 
			 *  \param time_text Time in string format */
			Time(const char *time_text);
			/** This constructor will attempt to convert the time given as
			 *  a string in the format HH:MM:SS 
			 *  \param time_text Time in string format */
			Time(const String &time_text);
			Time(const Time *t);
			Time(const Time &t);
			virtual ~Time();
			Time &operator=(const Time &t);
			/** Returns the current hour */
			virtual int Hour();
			/** Returns the current minute */
			virtual int Minute();
			/** Returns the current second */
			virtual int Second();
			/** Returns time in the following format:  HH:MM:SS */
			//const String &toString() const;
			/** This will return the time as a Unix formatted timestamp
			 *  counting the seconds from january 1st 1970 */
			const UInt32 timestamp();
	};

};

#endif
