/*
 * $Id$
 */
#ifndef __XVR2_GROUP_EXCEPTION_H__
#define __XVR2_GROUP_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	/** Generic exception for the group class */
	class GroupException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			GroupException();
	};


	/** This exception is thrown whenever you are trying to browse the group database for a specific entry and that entry is not available or non-existent */
	class GroupNotFound:public GroupException{
		public:
			/**
			 * Default constructor
			 */
			GroupNotFound();
	};
};

#endif

