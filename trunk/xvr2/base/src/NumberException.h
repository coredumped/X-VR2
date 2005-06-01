/*
 * $Id$
 */
#ifndef __XVR2_NUMBER_EXCEPTION_H__
#define __XVR2_NUMBER_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2{
	namespace Exception{

		/**
		 * Throw this exception when expecting a number in an operation and and receiving
		 * something different
		 */
		class Number:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Number();
		};
	};
};

#endif

