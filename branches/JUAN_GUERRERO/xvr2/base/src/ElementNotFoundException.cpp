/*
 * $Id$
 */
#include<ElementNotFoundException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		ElementNotFound::ElementNotFound(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ElementNotFoundException);
#endif
			description = (char *)xvr2::excepNoElem;
		}

	};
};

