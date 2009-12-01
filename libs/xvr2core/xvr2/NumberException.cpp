/*
 * $Id$
 */

#include"config.h"
#include "NumberException.h"
#include "MessageStrings.h"

namespace xvr2 {
	NumberException::NumberException(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2NumberException);
#endif
		description = (char *)xvr2::excepNumeric;
	}
};

