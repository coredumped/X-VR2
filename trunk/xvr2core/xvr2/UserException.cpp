/*
 * $Id$
 */
#include"config.h"
#include "UserException.h"
#include "MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		UserException::UserException(){
			description = (char *)xvr2::excepUser;
		}


		UserNotFound::UserNotFound(){
			description = (char *)xvr2::excepUserNotFound;
		}

	};
};


