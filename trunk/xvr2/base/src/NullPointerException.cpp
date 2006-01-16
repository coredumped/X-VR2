/*
 * $Id$
 */
#include<xvr2/NullPointerException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		NullPointer::NullPointer(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2NullPointerException);
#endif
			description = (char *)xvr2::excepNullPtr;
		}

	};
};

