/*
 * $Id$
 */
#include<ConditionVar.h>
#include<time.h>
#include<sys/time.h>
#include<errno.h>


namespace xvr2{
	
	void ConditionVar::destroy(){
		#ifdef USE_POSIX_THREADS
			pthread_cond_destroy(&__cvar);
		#endif
	}
	
	void ConditionVar::init(){
		#ifdef USE_POSIX_THREADS
			#ifdef USING_LINUX
				pthread_cond_init(&__cvar, NULL);
			#endif
		#endif
	}

	ConditionVar::ConditionVar(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2ConditionVar);
#endif
		init();
	}

	ConditionVar::~ConditionVar(){
		destroy();
	}

	void ConditionVar::signal(){
		#ifdef USE_POSIX_THREADS
			pthread_cond_signal(&__cvar);
		#endif
	}

	void ConditionVar::broadcast(){
		#ifdef USE_POSIX_THREADS
			pthread_cond_broadcast(&__cvar);
		#endif
	}

	void ConditionVar::wait(Mutex *m){
		#ifdef USE_POSIX_THREADS
			pthread_cond_wait(&__cvar, &m->mutex);
		#endif
	}

	void ConditionVar::timedWait(Mutex *m, long seconds, long nanoseconds){
		#ifdef USE_POSIX_THREADS
			struct timeval t1;
			struct timespec end;
			gettimeofday(&t1, NULL);
			end.tv_sec = seconds + t1.tv_sec;
			end.tv_nsec = nanoseconds + t1.tv_usec * 1000;
			if(pthread_cond_timedwait(&__cvar, &m->mutex, &end) == ETIMEDOUT)
				throw Exception::ConditionVarWaitTimedOut();
		#endif
	}

	void ConditionVar::wait(ConditionVar *cv, Mutex *m){
		#ifdef USE_POSIX_THREADS
			pthread_cond_wait(&cv->__cvar, &m->mutex);
		#endif
	}

	void ConditionVar::timedWait(ConditionVar *cv, Mutex *m, long seconds, long nanoseconds){
		#ifdef USE_POSIX_THREADS
			struct timeval t1;
			struct timespec end;
			gettimeofday(&t1, NULL);
			end.tv_sec = seconds + t1.tv_sec;
			end.tv_nsec = nanoseconds + t1.tv_usec * 1000;
			if(pthread_cond_timedwait(&cv->__cvar, &m->mutex, &end) == ETIMEDOUT)
				throw Exception::ConditionVarWaitTimedOut();
		#endif
	}

};
