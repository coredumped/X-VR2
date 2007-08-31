/*
 * $Id$
 */
#ifndef __MUTEX_EXCEPTION_H__
#define __MUTEX_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2{
	/**
	 * This is the generic exception thrown for mutexes
	 */
	class MutexException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			MutexException();
	};

	/**
	 * This exception is triggered when a deadlock is detected
	 */
	class DeadLock:public MutexException{
		public:
			/**
			 * Default constructor
			 */
			DeadLock();
	};

	/**
	 * This exception is used when a mutex failed to lock the current thread
	 */
	class UnableToLockMutex:public MutexException{
		public:
			/**
			 * Default constructor
			 */
			UnableToLockMutex();
	};

	/**
	 * This exception is used when a mutex failed to unlock the current thread
	 */
	class UnableToUnlockMutex:public MutexException{
		public:
			/**
			 * Default constructor
			 */
			UnableToUnlockMutex();
	};
};



#endif
