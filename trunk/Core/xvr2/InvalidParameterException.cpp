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
#include"xvr2config.h"
#include"InvalidParameterException.h"
#include"Memory.h"
#include"MessageStrings.h"
#include<string>
#if __GNUC__ < 3
#include<stdio.h>
#include"_xvr2ClassNames.h"
#endif


namespace xvr2 {

	InvalidParameter::InvalidParameter(){
		description = (char *)xvr2::excepInvalidParameter;	
	}

	InvalidParameter::InvalidParameter(const String &_param_name){
		description = (char *)xvr2::excepInvalidParameter;
		param_name = _param_name;
	}

}

