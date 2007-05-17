/*
 * $Id$
 */
#ifndef __XVR2_MEMORY_H__
#define __XVR2_MEMORY_H__
#include<System.h>
#include<Array.h>
#include<AutomatedGC.h>
#include<MemoryException.h>

namespace xvr2{
	/**
	 * This class deals with memory management and temporary
	 * allocated buffer.
	 * Temporary allocated buffer are like normal in-memory buffer
	 * structures, but as the name says they are temporary, after a
	 * specified ammount of time this buffers will be deleted from
	 * from memory so please be carefull while using them, they can
	 * help a lot but if you dont take the necesary safety measures
	 * they can <b>hurt</b> you a lot.
	 *
	 */
	class Memory:public System{
		private:
			AutomatedGC *garbage;
			bool usingGC;
		public:
			/**
			 * Calling this will initialize some 
			 * vital internal variables and cleanup
			 * processes
			 */
			Memory();
			~Memory();
			/**
			 * Using this will allocate <b>size</b>
			 * bytes in memory
			 */
			static void *allocBuffer(UInt32 size);
			/**
			 * Use this method to enlarge or minimize a buffer
			 */
			static void *reallocBuffer(void *buf, UInt32 newsize);
			/**
			 * Using this will deallocate the memory
			 * used by the buffer <b>buf</b>, call
			 * this method to deallocate memory 
			 * allocated by allocBuffer
			 */
			static void freeBuffer(void **buf);
			/**
			 * This will allocate a temporary memory buffer
			 * if <b>size</b> bytes with an expiration period
			 * of <b>timeout</b> seconds
			 */
			void *temporaryAlloc(UInt32 size, UInt32 timeout = 60);
			/**
			 * Use this method to clear or set every byte in a buffer
			 * to a specific value
			 */
			static void clearBuffer(void *buf, UInt32 siz, UInt8 value = 0);
			/** This allocate a buffer of size <b>siz</b> and will copy 
			 *  everything in <b>buf</b> to make an exact copy on the
			 *  newly created buffer */
			static void *duplicate(const void *buf, UInt32 siz);
			/** This will copy the contents of source and will put them
			 *  into destination */
			static void copy(void *destination, const void *source, UInt32 siz);
	};
};

#endif
