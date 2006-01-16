/*
 * $Id$
 */
#include<xvr2/NSTryAgainException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{
		NSTryAgain::NSTryAgain(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2NSTryAgainException);
#endif
			description = (char *)xvr2::excepNSTryAgain;
		}

	};
};

