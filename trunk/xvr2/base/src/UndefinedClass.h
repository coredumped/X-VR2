/*
 * $Id$
 * This class is not defined, are you sure this is the class you think it is?
 */
#ifndef __XVR2_UNDEFINED_CLASS_H__
#define __XVR2_UNDEFINED_CLASS_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	namespace Exception {
 		/**
 		 * \class UndefinedClass UndefinedClass.h
 		 * This exception is thrown whenever you try to access a class by a name
 		 * which is not the class's name.
 		 */
		class UndefinedClass:public Exception{
			public:
				/**
				 * Default constructor
				 */
				UndefinedClass();
		};
	};
};
 
#endif
