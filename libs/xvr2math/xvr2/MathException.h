/*
 * $Id$
 */
#ifndef __XVR2_MATH_EXCEPTION_H__
#define __XVR2_MATH_EXCEPTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {
	namespace Math {

		/** Generic mathematical exception */
		class MathException:public Exception{
			public:
				/**
				 * Default constructor
				 */
				MathException();
		};

	};
};


#endif
