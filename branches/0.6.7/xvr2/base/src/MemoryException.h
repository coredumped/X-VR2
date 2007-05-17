/*
 * $Id$
 */
#ifndef __XVR2_MEMORY_EXCEPTION_H__
#define __XVR2_MEMORY_EXCEPTION_H__
#include<Exception.h>

namespace xvr2 {
	namespace Exception{

		/** Generic memory exception */
		class Memory:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Memory();
		};


		/** A call to malloc or any other memory allocation routine has just failed, it may be posible that you are running out of memory or that this process is trying to allocate the maximum allowable memory size in the current system, sorry */
		class AllocationFailed:public Memory{
			public:
				/**
				 * Default constructor
				 */
				AllocationFailed();
		};


		/** I was unable to decrease/enlarge your memory buffer */
		class ReallocFailed:public Memory{
			public:
				/**
				 * Default constructor
				 */
				ReallocFailed();
		};

	};
};


#endif
