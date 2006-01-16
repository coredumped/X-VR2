/*
 * $Id$
 */
#ifndef __E4AL_SEMAPHORE_EXCEPTION_H__
#define __E4AL_SEMAPHORE_EXCEPTION_H__
#include<xvr2/ThreadException.h>

namespace xvr2 {
	namespace Exception{

		/** Generic semaphore exception */
		class Semaphore:public Thread{
			public:
				/**
				 * Default constructor
				 */
				Semaphore();
		};


		/** The initialization value for this semaphore is too big, unable to create semaphore, sorry */
		class SemaphoreInitValue:public Semaphore{
			public:
				/**
				 * Default constructor
				 */
				SemaphoreInitValue();
		};


		/** I'm unable to destroy this semaphore right now, maybe one or more threads are waiting for it */
		class SemaphoreUnableToDestroy:public Semaphore{
			public:
				/**
				 * Default constructor
				 */
				SemaphoreUnableToDestroy();
		};


		/** Unable to decrease this semaphore's value, it is already very low */
		class SemaphoreUnableToDecrease:public Semaphore{
			public:
				/**
				 * Default constructor
				 */
				SemaphoreUnableToDecrease();
		};


		/** I'm unable to increase the value of this semaphore right now is bigger than the maximum defined by this thread implementation, sorry */
		class SemaphoreUnableToIncrease:public Semaphore{
			public:
				/**
				 * Default constructor
				 */
				SemaphoreUnableToIncrease();
		};

	};
};


#endif
