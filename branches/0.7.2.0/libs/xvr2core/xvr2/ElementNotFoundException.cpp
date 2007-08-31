/*
 * $Id$
 */
#include"config.h"
#include"ElementNotFoundException.h"
#include"MessageStrings.h"

namespace xvr2 {
	ElementNotFound::ElementNotFound(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ElementNotFoundException);
#endif
		description = (char *)xvr2::excepNoElem;
	}
};

