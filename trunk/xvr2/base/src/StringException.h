/*
 * $Id$
 */
#ifndef __XVR2_STRING_EXCEPTION_H__
#define __XVR2_STRING_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	namespace Exception{

		/** Generic String exception */
		class Stringe:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Stringe();
		};

	};
};


#endif

