/*
 * $Id$
 */
#include"config.h"
#include"GroupException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		GroupException::GroupException(){
			description = (char *)xvr2::excepGroup;
		}


		GroupNotFound::GroupNotFound(){
			description = (char *)xvr2::excepGroupNotFound;
		}


	};
};


