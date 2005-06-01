/*
 * $Id$
 */
#ifndef __XVR2_CRONOMETER_H__
#define __XVR2_CRONOMETER_H__

#include<xvr2/Time.h>
#include<sys/time.h>

namespace xvr2{
	/**
	 * This class deals with time counters
	 */
	class Chronometer:protected Time{
		protected:
			struct timeval _startedOn;
			struct timeval _finishedOn;
			bool   _counting;
		public:
			/** Default constructor, it does nothing */
			Chronometer();
			/** This will start the chronometer counter and 
			 *  will reset any previous counter value */
			void start();
			/** This will stop the counter */
			void stop();
			/** If you stop the counter, this methid will 
			 *  resume the count */
			void resume();
			/** This will reset your counter without stoping it */
			void reset();
			/** This will return the elapsed hours since you called start */
			long int elapsedHour();
			/** This will return the elapsed munutes since you called start */
			long int elapsedMinute();
			/** This will return the elapsed second since you called start */
			long int elapsedSecond();
			/** This will return the elapsed millisecond since you called start */
			long int elapsedMillisecond();
			/** This will return the elapsed microsecond since you called start */
			long int elapsedMicrosecond();
	};
};

#endif
