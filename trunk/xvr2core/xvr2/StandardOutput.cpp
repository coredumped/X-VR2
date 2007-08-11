/*
 * $Id$
 */
#include"config.h"
#include "StandardOutput.h"
#include<iostream>

namespace xvr2{
	StandardOutput::StandardOutput(){
	}

	void StandardOutput::outputMethod(const void *buf, UInt32 size){
		std::cout.write((const char *)buf, size);
		std::cout.flush();
	}
};
