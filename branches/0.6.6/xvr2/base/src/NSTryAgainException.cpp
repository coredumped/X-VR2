/*
 * $Id$
 */
#include<NSTryAgainException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{
		NSTryAgain::NSTryAgain(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NSTryAgainException);
#endif
			description = (char *)xvr2::excepNSTryAgain;
		}

	};
};

