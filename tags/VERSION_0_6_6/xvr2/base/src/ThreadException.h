/*
 * $Id$
 */
#ifndef __E4AL_THREAD_EXCEPTION_H__
#define __E4AL_THREAD_EXCEPTION_H__
#include<Exception.h>

namespace xvr2 {
	namespace Exception{

		/**
		 * Thread Generic Exception
		 */
		class Thread:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Thread();
		};

		/**
		 * If you try to execute an operation that can only be placed
		 * over a running Thred and you're current thread is not running yet
		 * this is the exception that is going to be thrown */
		class ThreadNotRunning:public Thread{
			public:
				/**
				 * Default constructor
				 */
				ThreadNotRunning();
		};

		/** The condition variable was signaled before wait interval has been reached, as a consecuence the controlled Mutex will be re-acquired */
		class ConditionVarWaitTimedOut:public Thread{
			public:
				/**
				 * Default constructor
				 */
				ConditionVarWaitTimedOut();
		};

	};
};


#endif

