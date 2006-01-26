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
#endif


namespace xvr2 {
	namespace Exception{

		InvalidParameter::InvalidParameter(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2InvalidParameterException);
#endif
			description = (char *)xvr2::excepInvalidParameter;	
		}

		InvalidParameter::InvalidParameter(const char *param_name){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2InvalidParameterException);
#endif
			description = (char *)xvr2::Memory::allocBuffer(strlen((char *)xvr2::excepInvalidParameter) + 30 + strlen(param_name));
			sprintf(description, "%s, Parameter: %s", (char *)xvr2::excepInvalidParameter, param_name);
		}

		InvalidParameter::~InvalidParameter(){
			if((char *)description == (char *)xvr2::excepInvalidParameter){
				xvr2::Memory::freeBuffer((void **)&description);
			}
		}

	};
};

