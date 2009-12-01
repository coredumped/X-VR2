/*
 * $Id$
 */
#include"config.h"
#include "UserException.h"
#include "MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		UserException::UserException(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2UserException);
#endif
			description = (char *)xvr2::excepUser;
		}


		UserNotFound::UserNotFound(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2UserNotFoundException);
#endif
			description = (char *)xvr2::excepUserNotFound;
		}

	};
};


