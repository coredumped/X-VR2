/*
 * $Id$
 */
#ifndef __XVR2_STRING_EXCEPTION_H__
#define __XVR2_STRING_EXCEPTION_H__
#include<Exception.h>

namespace xvr2 {
	namespace Exception{

		/** Generic String exception */
		class String:public Exception{
			public:
				/**
				 * Default constructor
				 */
				String();
		};

	};
};


#endif

