/*
 * $Id$
 *
 *                 Juan V. Guerrero <coredumped@esolutions4all.com>
 */
#ifndef __XVR2_TIME_H__
#define __XVR2_TIME_H__
#include<Date.h>

namespace xvr2{

	/**
	 * This class represents the time object
	 */
	class Time:protected Date{
		public:
			/** Default constructor, it does nothing */
			Time();
			/** This will initialize all internal variables to the
			 *  timestamp <b>tstamp</b> */	 
			Time(UInt32 tstamp);
			/** This will initialize the internal values to the corresponding
			 * <b>hour, min</b> and <b>sec</b>. */
			Time(int hour, int min, int sec);
			virtual ~Time(){;}
			/** Returns the current hour */
			virtual int Hour();
			/** Returns the current minute */
			virtual int Minute();
			/** Returns the current second */
			virtual int Second();
			/** Returns time in the following format:  HH:MM:SS */
			const String &toString();
			/** This will return the time as a Unix formatted timestamp
			 *  counting the seconds from january 1st 1970 */
			const UInt32 timestamp();
	};

};

#endif
