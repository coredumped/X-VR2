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
}
