/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_MEMORY_H__
#define __XVR2_MEMORY_H__
#include<xvr2/System.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/Buffer.h>

namespace xvr2{
	/** This class implement basic memory management tasks.
	 *  @todo See if there is really a need for this class. */
	class Memory:public System{
		public:
			/**
			 * Calling this will initialize some 
			 * vital internal variables and cleanup
			 * processes
			 */
			Memory();
			~Memory();
			/** Using this will allocate <b>size</b>
			 *  bytes in memory. */
			static void *allocBuffer(UInt32 size);
			static Buffer alloc(UInt32 size);
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
}

#endif
