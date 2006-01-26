/*
 * $Id$
 */
#ifndef __XVR2_USER_EXCEPTION_H__
#define __XVR2_USER_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	/** Generic exception of the user class */
	class UserException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			UserException();
	};

	/** This exception is thrown whenever you are trying to browse the user database for a specific entry and that entry is not available or non-existent */
	class UserNotFound:public UserException{
		public:
			/**
			 * Default constructor
			 */
			UserNotFound();
	};
};


#endif

