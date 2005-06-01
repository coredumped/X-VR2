/*
 * $Id$
 */
#include<xvr2/SecurityException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{
		Security::Security(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SecurityException);
#endif
			description = (char *)xvr2::excepSecurity;
		}

		UserIDDoesNotMatch::UserIDDoesNotMatch(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UserIDDoesNotMatchException);
#endif
			description = (char *)xvr2::excepUserIDDoesNotMatch;
		}
	};
};

