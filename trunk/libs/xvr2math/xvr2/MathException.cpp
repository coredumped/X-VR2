/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include"_xvr2mathClassNames.h"
#include<xvr2/MathException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Math {

		MathException::MathException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Math_MathException);
#endif
			description = (char *)xvr2::excepMath;
		}

	};
};

