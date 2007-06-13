/*
 * $Id$
 */
#include"config.h"
#include "NullPointerException.h"
#include "MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		NullPointer::NullPointer(){
			description = (char *)xvr2::excepNullPtr;
		}

	};
};

