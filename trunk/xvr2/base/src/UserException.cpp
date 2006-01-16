/*
 * $Id$
 */
#include<xvr2/UserException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		User::User(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2UserException);
#endif
			description = (char *)xvr2::excepUser;
		}


		UserNotFound::UserNotFound(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2UserNotFoundException);
#endif
			description = (char *)xvr2::excepUserNotFound;
		}

	};
};


