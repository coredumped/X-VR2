/*
 * $Id$
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
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2InvalidParameter);
#endif
		description = (char *)xvr2::excepInvalidParameter;	
	}

	InvalidParameter::InvalidParameter(const String &_param_name){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2InvalidParameter);
#endif
		description = (char *)xvr2::excepInvalidParameter;
		param_name = _param_name;
	}

};

