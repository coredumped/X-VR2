/*
 * $Id$
 */
#include<HostNotFoundException.h>
#include<MessageStrings.h>
namespace xvr2 {
	namespace Exception{

		HostNotFound::HostNotFound(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2HostNotFoundException);
#endif
			description = (char *)xvr2::excepHostNotFound;
		}

	};
};

