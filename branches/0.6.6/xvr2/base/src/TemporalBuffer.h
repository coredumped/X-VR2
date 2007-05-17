/*
 * $Id$
 */
#ifndef __TEMPORAL_BUFFER_H__
#define __TEMPORAL_BUFFER_H__
#include<System.h>

namespace xvr2{

	/**
	 * This class identifies a temporary memory object
	 * it is intended to be used by the garbage collector
	 * Please be carefull while using temporary memory buffers
	 * because after the timeout has been reached all the 
	 * memory it is storing will be PERMANENTLY ERASED
	 */
	class TemporalBuffer:public System{
		protected:
			/**
			 * This variable holds current elapsed time
			 * since the buffer was allocated
			 */
			UInt32 _elapsed;
			/**
			 * Live timeout in seconds, after this period
			 * expires all memory allocated for this
			 * buffer will be released
			 */
			UInt32 _timeout;
		public:
			/** 
			 * This is the memory buffer as intended
			 * to be
			 */
			void *buffer;
			UInt32 started;
			/** 
			 * Default constructor, this will initialize
			 * the buffer memory address to 0x0000 and
			 * also the timeout
			 */
			TemporalBuffer();
			TemporalBuffer(UInt32 size, UInt32 t);
			void *alloc(UInt32 size);
			void free();
			UInt32 elapsed();
			UInt32 timeout();
	};

};
#endif
