/*
 * $Id$
 */
#include<xvr2/NoIPForYouException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2{
	namespace Exception{

		NoIPForYou::NoIPForYou(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2NoIPForYouException);
#endif
			description = (char *)xvr2::excepNoIPForYou;
		}

	};
};

