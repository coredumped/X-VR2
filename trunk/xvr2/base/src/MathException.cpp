/*
 * $Id$
 */
#include<xvr2/MathException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Math::Math(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2MathException);
#endif
			description = (char *)xvr2::excepMath;
		}

	};
};

