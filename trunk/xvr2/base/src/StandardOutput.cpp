/*
 * $Id$
 */
#include<xvr2/StandardOutput.h>
#include<iostream>

namespace xvr2{
	StandardOutput::StandardOutput(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2StandardOutput);
#endif
	}

	void StandardOutput::outputMethod(const void *buf, UInt32 size){
		std::cout.write((const char *)buf, size);
		std::cout.flush();
	}
};
