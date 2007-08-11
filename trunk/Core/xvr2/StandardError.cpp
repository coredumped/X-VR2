/*
 * $Id$
 */
#include"config.h"
#include "StandardError.h"
#include<iostream>

namespace xvr2{
	StandardError::StandardError(){
	}

	void StandardError::outputMethod(const void *buf, UInt32 size){
		if(size > 0){
			std::cerr.write((const char *)buf, size);
			std::cerr.flush();
		}
	}
};
