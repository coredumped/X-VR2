/*
 * $Id$
 */
#include<ArrayIndexOutOfLimitsException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ArrayIndexOutOfLimitsException);
#endif
			description = (char *)xvr2::excepAOB;	
		}
		
	};
};
