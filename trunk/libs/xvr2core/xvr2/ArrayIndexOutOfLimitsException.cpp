/*
 * $Id$
 */
#include"config.h"
#include"ArrayIndexOutOfLimitsException.h"
#include"MessageStrings.h"

namespace xvr2 {
	ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(){
		description = (char *)xvr2::excepAOB;	
		_i = -1;
		_m = -1;
	}

	ArrayIndexOutOfLimits::ArrayIndexOutOfLimits(int _index, int _maxval){
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
