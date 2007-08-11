/*
 * $Id$
 */
#ifndef __XVR2_MEMORY_EXCEPTION_H__
#define __XVR2_MEMORY_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	/** Generic memory exception */
	class MemoryException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			MemoryException();
	};


	/** A call to malloc or any other memory allocation routine has just failed, it may be posible that you are running out of memory or that this process is trying to allocate the maximum allowable memory size in the current system, sorry */
	class AllocationFailed:public MemoryException{
		public:
			/**
			 * Default constructor
			 */
			AllocationFailed();
	};


	/** I was unable to decrease/enlarge your memory buffer */
	class ReallocFailed:public MemoryException{
		public:
			/**
			 * Default constructor
			 */
			ReallocFailed();
	};
};


#endif
