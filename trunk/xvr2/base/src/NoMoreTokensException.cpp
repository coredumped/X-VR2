/*
 * $Id$
 */
#include<xvr2/NoMoreTokensException.h>
#include<xvr2/MessageStrings.h>

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

