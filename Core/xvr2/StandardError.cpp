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
}
