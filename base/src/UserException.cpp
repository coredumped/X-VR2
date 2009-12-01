/*
 * $Id$
 */
#include<UserException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		User::User(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UserException);
#endif
			description = (char *)xvr2::excepUser;
		}


		UserNotFound::UserNotFound(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UserNotFoundException);
#endif
			description = (char *)xvr2::excepUserNotFound;
		}

	};
};


