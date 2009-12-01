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
#include "System.h"
#include<unistd.h>
#ifdef USING_LINUX
#include "SharedVar.h"
#include<cstdio>
#include<Memory.h>
#include "String.h"
#endif

namespace xvr2{

	System::System(){
	}

	void System::usleep(UInt32 usec){
		::usleep(usec);
	}
}
