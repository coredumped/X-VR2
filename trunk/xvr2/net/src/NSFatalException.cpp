/*
 * $Id$
 */
#include<xvr2/NSFatalException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		NSFatal::NSFatal(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2NSFatalException);
#endif
			description = (char *)xvr2::excepNSFatal;
		}

	};
};

