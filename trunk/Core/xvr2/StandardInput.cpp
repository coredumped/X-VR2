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
#include "StandardInput.h"
#include<iostream>

namespace xvr2{

	StandardInput::StandardInput(){
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
}
