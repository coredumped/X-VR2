/*
 * $Id$
 */
#include<xvr2/GroupException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Group::Group(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2GroupException);
#endif
			description = (char *)xvr2::excepGroup;
		}


		GroupNotFound::GroupNotFound(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2GroupNotFoundException);
#endif
			description = (char *)xvr2::excepGroupNotFound;
		}


	};
};


