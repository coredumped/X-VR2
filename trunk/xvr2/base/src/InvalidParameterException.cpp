/*
 * $Id$
 */
#include<xvr2/InvalidParameterException.h>
#include<xvr2/Memory.h>
#include<xvr2/MessageStrings.h>
#include<string>
#ifndef USING_GCC3
#include<stdio.h>
#endif


namespace xvr2 {
	namespace Exception{

		InvalidParameter::InvalidParameter(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2InvalidParameterException);
#endif
			description = (char *)xvr2::excepInvalidParameter;	
		}

		InvalidParameter::InvalidParameter(const char *param_name){
#ifndef USING_GCC3
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

