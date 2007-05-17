/*
 * $Id$
 */
#ifndef __SHARED_VAR_h__
#define __SHARED_VAR_h__

#include<xvr2/Threading.h>
#include<xvr2/Mutex.h>
#ifdef USE_POSIX_THREADS
#include<pthread.h>
#endif

namespace xvr2{
	/**
	 * Condition variables is another type of synchronization device
	 * unlike the Mutex how locks and unlocks a thread, this devide does
	 * somethings a bit different, this one waits for a condition to be
	 * reached, if the condition in fact has been accomplished it will
	 * lock and unlock a thread or a set of threads that might be waiting 
	 * for a conditiond to be reached on that specific ConditionVar object
	 *
	 */
	class ConditionVar:public Threading{
		private:
		protected:
#ifdef USE_POSIX_THREADS
			pthread_cond_t __cvar;
#endif
			void init();
			void destroy();
		public:
			ConditionVar();
			~ConditionVar();
			/** This will restart just one of the threads that are
			 *  waiting for the condition to be reached
			 */
			void signal();
			/** This will restart all the threads that are
			 *  waiting for the condition to be reached
			 */
			void broadcast();
			/** This will unlock the Mutex <b>mutex</b> and will wait
			 *  for this condition variable to be signaled
			 */
			void wait(Mutex *mutex);
			/** This will unlock the Mutex <b>mutex</b> and will wait
			 *  for this condition variable to be signaled
			 */
			void timedWait(Mutex *mutex, long seconds = 1, long nanoseconds = 0);
			/** This is the static version of the wait method */
			static void wait(ConditionVar *cv, Mutex *mutex);
			/** This is the static version of the timedWait method */
			static void timedWait(ConditionVar *cv, Mutex *mutex, long seconds = 1, long nanoseconds = 0);
	};
};

#endif
