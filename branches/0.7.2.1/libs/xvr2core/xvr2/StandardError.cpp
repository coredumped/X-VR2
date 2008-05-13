/*
 * $Id$
 */
#include"config.h"
#include "StandardError.h"
#include<iostream>

namespace xvr2{
	StandardError::StandardError(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(xvr2::_xvr2StandardError);
#endif
	}

	void StandardError::outputMethod(const void *buf, UInt32 size){
		if(size > 0){
			std::cerr.write((const char *)buf, size);
			std::cerr.flush();
		}
	}
};
