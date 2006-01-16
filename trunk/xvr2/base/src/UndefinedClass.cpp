/*
 * $Id$
 */
#include<xvr2/UndefinedClass.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception {
	
		UndefinedClass::UndefinedClass(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2UndefinedClassException);
#endif
			description = (char *)xvr2::excepUndefinedClass;
		}
		
	};
};
