/*
 * $Id$
 */
#include<Chronometer.h>


namespace xvr2{

	/* set current timezone to GMT 0 */
	static struct timezone __currentTZGMT0;

	/* this function was extracted from the libc info manual */
	int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y){
		if (x->tv_usec < y->tv_usec) {
			int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
			y->tv_usec -= 1000000 * nsec;
			y->tv_sec += nsec;
		}
		if (x->tv_usec - y->tv_usec > 1000000) {
			int nsec = (x->tv_usec - y->tv_usec) / 1000000;
			y->tv_usec += 1000000 * nsec;
			y->tv_sec -= nsec;
		}
		result->tv_sec = x->tv_sec - y->tv_sec;
		result->tv_usec = x->tv_usec - y->tv_usec;
		return x->tv_sec < y->tv_sec;
	}




	Chronometer::Chronometer(){
		_counting = false;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Chronometer);
#endif
	}

	void Chronometer::start(){
		gettimeofday(&_startedOn, &__currentTZGMT0);
		_counting = true;
	}

	void Chronometer::stop(){
		gettimeofday(&_finishedOn, &__currentTZGMT0);
		_counting = false;
	}

	void Chronometer::resume(){
		_counting = true;
	}

	void Chronometer::reset(){
		gettimeofday(&_startedOn, &__currentTZGMT0);
	}

	long int Chronometer::elapsedHour(){
		struct timeval current, result;
		long int value;
		if(_counting){
			gettimeofday(&current, &__currentTZGMT0);
			timeval_subtract (&result, &current, &_startedOn);
			value = result.tv_sec;
		}
		else{
			timeval_subtract (&result, &_finishedOn, &_startedOn);
			value = result.tv_sec;
		}
		return (value % 3600);
	}

	long int Chronometer::elapsedMinute(){
		struct timeval current, result;
		long int value;
		if(_counting){
			gettimeofday(&current, &__currentTZGMT0);
			timeval_subtract (&result, &current, &_startedOn);
			value = result.tv_sec;
		}
		else{
			timeval_subtract (&result, &_finishedOn, &_startedOn);
			value = result.tv_sec;
		}
		return (value % 60);
	}

	long int Chronometer::elapsedSecond(){
		struct timeval current, result;
		long int value;
		if(_counting){
			gettimeofday(&current, &__currentTZGMT0);
			timeval_subtract (&result, &current, &_startedOn);
			value = result.tv_sec;
		}
		else{
			timeval_subtract (&result, &_finishedOn, &_startedOn);
			value = result.tv_sec;
		}
		return value;
	}

	long int Chronometer::elapsedMillisecond(){
		struct timeval current, result;
		long int value;
		if(_counting){
			gettimeofday(&current, &__currentTZGMT0);
			timeval_subtract (&result, &current, &_startedOn);
			value = _finishedOn.tv_usec;
			value = result.tv_sec;
		}
		else{
			timeval_subtract (&result, &_finishedOn, &_startedOn);
			value = result.tv_usec;
		}
		return value % 1000;
	}

	long int Chronometer::elapsedMicrosecond(){
		struct timeval current, result;
		long int value;
		if(_counting){
			gettimeofday(&current, &__currentTZGMT0);
			timeval_subtract (&result, &current, &_startedOn);
			value = result.tv_usec;
		}
		else{
			timeval_subtract (&result, &_finishedOn, &_startedOn);
			value = result.tv_usec;
		}
		return value;
	}


};