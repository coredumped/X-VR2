/*
 * $Id$
 */
#include"config.h"
#include"ArrayIndexOutOfLimitsException.h"
#include"MessageStrings.h"

namespace xvr2 {
	ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ArrayIndexOutOfLimitsException);
#endif
		description = (char *)xvr2::excepAOB;	
	}
};
