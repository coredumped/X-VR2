/*
 * $Id$
 */
#include<StringException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		String::String(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2StringException);
#endif
			description = (char *)xvr2::excepString;
		}

	};
};


