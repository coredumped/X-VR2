/*
 * $Id$
 */
#include"config.h"
#include "NoMoreTokensException.h"
#include "MessageStrings.h"

namespace xvr2{
	namespace Exception{

		NoMoreTokens::NoMoreTokens(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2NoMoreTokensException);
#endif
			description = (char *)xvr2::excepNoTokens;
		}

	};
};

