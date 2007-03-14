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
		_i = -1;
		_m = -1;
	}

	ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(int _index, int _maxval){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ArrayIndexOutOfLimitsException);
#endif
		description = (char *)xvr2::excepAOB;	
		_i = _index;
		_m = _maxval;
	}

	int ArrayIndexOutOfLimits::index(){
		return _i;
	}

	int ArrayIndexOutOfLimits::maxval(){
		return _m;
	}
};
