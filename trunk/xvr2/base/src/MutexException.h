/*
 * $Id$
 */
#ifndef __MUTEX_EXCEPTION_H__
#define __MUTEX_EXCEPTION_H__
#include<Exception.h>

namespace xvr2{
	namespace Exception{

		/**
		 * This is the generic exception thrown for mutexes
		 */
		class Mutex:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Mutex();
		};

		/**
		 * This exception is triggered when a deadlock is detected
		 */
		class DeadLock:public Mutex{
			public:
				/**
				 * Default constructor
				 */
				DeadLock();
		};

		/**
		 * This exception is used when a mutex failed to lock the current thread
		 */
		class UnableToLockMutex:public Mutex{
			public:
				/**
				 * Default constructor
				 */
				UnableToLockMutex();
		};

		/**
		 * This exception is used when a mutex failed to unlock the current thread
		 */
		class UnableToUnlockMutex:public Mutex{
			public:
				/**
				 * Default constructor
				 */
				UnableToUnlockMutex();
		};


	};
};



#endif
