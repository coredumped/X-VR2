/*
 * $Id$
 */
#include<StringException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Stringe::Stringe(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2StringException);
#endif
			description = (char *)xvr2::excepString;
		}

	};
};


