/*
 * $Id$
 */
#include"config.h"
#include "NoMoreTokensException.h"
#include "MessageStrings.h"

namespace xvr2{
	namespace Exception{

		NoMoreTokens::NoMoreTokens(){
			description = (char *)xvr2::excepNoTokens;
		}

	};
};

