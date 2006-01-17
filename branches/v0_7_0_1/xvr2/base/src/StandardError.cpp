/*
 * $Id$
 */
#include<xvr2/StandardError.h>
#include<iostream>

namespace xvr2{
	StandardError::StandardError(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2StandardError);
#endif
	}

	void StandardError::outputMethod(const void *buf, UInt32 size){
		std::cerr.write((const char *)buf, size);
		std::cerr.flush();
	}
};
