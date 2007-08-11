/*
 * $Id$
 */

#include"config.h"
#include "NumberException.h"
#include "MessageStrings.h"

namespace xvr2 {
	NumberException::NumberException(){
		description = (char *)xvr2::excepNumeric;
	}
};

