/*
 * $Id$
 */
#include<xvr2/StringException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Stringe::Stringe(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2StringException);
#endif
			description = (char *)xvr2::excepString;
		}

	};
};

