/*
 * $Id$
 */
#ifndef __XVR2_NULL_POINTER_EXCEPTION_H__
#define __XVR2_NULL_POINTER_EXCEPTION_H__
#include<Exception.h>

namespace xvr2{
	namespace Exception{
		/**
		 * Throw this exception when doing something that is not appropiate with
		 * a null pointer
		 */
		class NullPointer:public Exception{
			public:
				/**
				 * Default constructor
				 */
				NullPointer();
		};
	};
};


#endif
