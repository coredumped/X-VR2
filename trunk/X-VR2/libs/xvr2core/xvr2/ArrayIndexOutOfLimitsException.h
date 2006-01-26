/*
 * $Id$
 */
#ifndef __XVR2_ARRAY_OUT_OF_LIMITS_EXCEPTION_H__
#define __XVR2_ARRAY_OUT_OF_LIMITS_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2{
	/**
	 * Throw this exception when an operation over an array exceeds is inbound
	 * and outbound limits
	 */
	class ArrayIndexOutOfLimits:public Exception{
		public:
			/**
			 * Default constructor
			 */
			ArrayIndexOutOfLimits();
	};
};
#endif
