/*
 * $Id$
 */
#ifndef __XVR2_SECURITY_EXCEPTION_H__
#define __XVR2_SECURITY_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	/**
	 * This is a generic exception for security-related events
	 */
	class Security:public Exception{
		public:
			/**
			 * Default constructor
			 */
			Security();
	};
	
	/**
	 * This is a generic exception for security-related events
	 */
	class UserIDDoesNotMatch:public Security{
		public:
			/**
			 * Default constructor
			 */
			UserIDDoesNotMatch();
	};
};


#endif
