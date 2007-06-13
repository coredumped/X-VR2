/*
 * $Id$
 */
#include"config.h"
#include"ElementNotFoundException.h"
#include"MessageStrings.h"

namespace xvr2 {
	ElementNotFound::ElementNotFound(){
		description = (char *)xvr2::excepNoElem;
	}
};

