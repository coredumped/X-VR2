/*
 * $Id$
 */
#ifndef __XVR2_GROUP_EXCEPTION_H__
#define __XVR2_GROUP_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	namespace Exception{

		/** Generic exception for the group class */
		class Group:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Group();
		};


		/** This exception is thrown whenever you are trying to browse the group database for a specific entry and that entry is not available or non-existent */
		class GroupNotFound:public Group{
			public:
				/**
				 * Default constructor
				 */
				GroupNotFound();
		};

	};
};


#endif

