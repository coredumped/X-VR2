/*
 * $Id$
 */
#include<xvr2/BufferTooSmall.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception {
		
		BufferTooSmall::BufferTooSmall(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2BufferTooSmallException);
#endif
			description = (char *)xvr2::excepBufferTooSmall;
		}
		
	};
};
