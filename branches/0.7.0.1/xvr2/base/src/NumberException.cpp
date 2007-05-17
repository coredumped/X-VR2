/*
 * $Id$
 */

#include<xvr2/NumberException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Number::Number(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2NumberException);
#endif
			description = (char *)xvr2::excepNumeric;
		}

	};
};

