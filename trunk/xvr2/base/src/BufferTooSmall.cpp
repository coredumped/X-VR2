/*
 * $Id$
 */
#include<BufferTooSmall.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception {
		
		BufferTooSmall::BufferTooSmall(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2BufferTooSmallException);
#endif
			description = (char *)xvr2::excepBufferTooSmall;
		}
		
	};
};
