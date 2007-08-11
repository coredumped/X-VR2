/*
 * $Id$
 */
#ifndef __E4AL_THREAD_EXCEPTION_H__
#define __E4AL_THREAD_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	/**
	 * ThreadException Generic Exception
	 */
	class ThreadException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			ThreadException();
	};

	/**
	 * If you try to execute an operation that can only be placed
	 * over a running Thred and you're current thread is not running yet
	 * this is the exception that is going to be thrown */
	class ThreadNotRunning:public ThreadException{
		public:
			/**
			 * Default constructor
			 */
			ThreadNotRunning();
	};

	/** The condition variable was signaled before wait interval has been reached, as a consecuence the controlled Mutex will be re-acquired */
	class ConditionVarWaitTimedOut:public ThreadException{
		public:
			/**
			 * Default constructor
			 */
			ConditionVarWaitTimedOut();
	};
};


#endif

