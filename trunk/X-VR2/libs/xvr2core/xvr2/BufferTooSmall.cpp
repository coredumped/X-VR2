/*
 * $Id$
 */
#include"config.h"
#include"BufferTooSmall.h"
#include"MessageStrings.h"

namespace xvr2 {
	BufferTooSmall::BufferTooSmall(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2BufferTooSmallException);
#endif
		description = (char *)xvr2::excepBufferTooSmall;
	}
};
