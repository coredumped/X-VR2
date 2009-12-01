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
#include"DSO.h"
#include"DSObject.h"
#include<dlfcn.h>

namespace xvr2 {

	static void forced_verification(){
		DSObjectFactory::create<String>(0);
		DSObjectFactory::destroy<String>(0, 0);
	}
	
	void __dummy_func_only_used_to_clear_a_warning(){
		forced_verification();
	}

}
