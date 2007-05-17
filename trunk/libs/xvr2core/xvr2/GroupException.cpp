/*
 * $Id$
 */
#include"config.h"
#include"GroupException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		GroupException::GroupException(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2GroupException);
#endif
			description = (char *)xvr2::excepGroup;
		}


		GroupNotFound::GroupNotFound(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2GroupNotFoundException);
#endif
			description = (char *)xvr2::excepGroupNotFound;
		}


	};
};


