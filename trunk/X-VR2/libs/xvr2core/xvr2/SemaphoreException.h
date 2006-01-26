/*
 * $Id$
 */
#ifndef __E4AL_SEMAPHORE_EXCEPTION_H__
#define __E4AL_SEMAPHORE_EXCEPTION_H__
#include<xvr2/ThreadException.h>

namespace xvr2 {
	/** Generic semaphore exception */
	class SemaphoreException:public ThreadException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreException();
	};


	/** The initialization value for this semaphore is too big, unable to create semaphore, sorry */
	class SemaphoreInitValue:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreInitValue();
	};


	/** I'm unable to destroy this semaphore right now, maybe one or more threads are waiting for it */
	class SemaphoreUnableToDestroy:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreUnableToDestroy();
	};


	/** Unable to decrease this semaphore's value, it is already very low */
	class SemaphoreUnableToDecrease:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreUnableToDecrease();
	};


	/** I'm unable to increase the value of this semaphore right now is bigger than the maximum defined by this thread implementation, sorry */
	class SemaphoreUnableToIncrease:public SemaphoreException{
		public:
			/**
			 * Default constructor
			 */
			SemaphoreUnableToIncrease();
	};
};


#endif
