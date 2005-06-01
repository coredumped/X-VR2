/*
 * $Id$
 */
#ifndef __XVR2_MATH_EXCEPTION_H__
#define __XVR2_MATH_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	namespace Exception{

		/** Generic mathematical exception */
		class Math:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Math();
		};

	};
};


#endif
