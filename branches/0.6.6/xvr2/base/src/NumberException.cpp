/*
 * $Id$
 */

#include<NumberException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Number::Number(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NumberException);
#endif
			description = (char *)xvr2::excepNumeric;
		}

	};
};

