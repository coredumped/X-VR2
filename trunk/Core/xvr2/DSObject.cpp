/*
 * $Id$
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

};