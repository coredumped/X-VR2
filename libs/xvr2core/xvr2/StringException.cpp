/*
 * $Id$
 */
#include"config.h"
#include "StringException.h"
#include "MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		Stringe::Stringe(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2StringException);
#endif
			description = (char *)xvr2::excepString;
		}

	};
};


