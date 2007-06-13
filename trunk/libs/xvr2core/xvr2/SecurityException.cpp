/*
 * $Id$
 */
#include"config.h"
#include "SecurityException.h"
#include "MessageStrings.h"

namespace xvr2 {
	namespace Exception{
		Security::Security(){
			description = (char *)xvr2::excepSecurity;
		}

		UserIDDoesNotMatch::UserIDDoesNotMatch(){
			description = (char *)xvr2::excepUserIDDoesNotMatch;
		}
	};
};

