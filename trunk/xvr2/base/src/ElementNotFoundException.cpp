/*
 * $Id$
 */
#include<xvr2/ElementNotFoundException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		ElementNotFound::ElementNotFound(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ElementNotFoundException);
#endif
			description = (char *)xvr2::excepNoElem;
		}

	};
};

