/*
 * $Id$
 */
#include<NSFatalException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		NSFatal::NSFatal(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NSFatalException);
#endif
			description = (char *)xvr2::excepNSFatal;
		}

	};
};

