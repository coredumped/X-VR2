/*
 * $Id$
 */
#include<NoMoreTokensException.h>
#include<MessageStrings.h>

namespace xvr2{
	namespace Exception{

		NoMoreTokens::NoMoreTokens(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NoMoreTokensException);
#endif
			description = (char *)xvr2::excepNoTokens;
		}

	};
};

