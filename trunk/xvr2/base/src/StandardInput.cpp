/*
 * $Id$
 */
#include<xvr2/StandardInput.h>
#include<iostream>

namespace xvr2{

	StandardInput::StandardInput(){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2StandardInput);
#endif
	}

	void StandardInput::inputMethod(void *buf, UInt32 size){
		if(size == 1){
			char c;
			std::cin.get(c);
			((char *)buf)[0] = c;
		}
		else{
			std::cin.getline((char *)buf, size);
		}
	}
};
