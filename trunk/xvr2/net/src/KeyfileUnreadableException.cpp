/*
 * $Id$
 */
#include<xvr2/KeyfileUnreadableException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_KeyfileUnreadable = "xvr2::Exception::KeyfileUnreadable";
#endif
		static const char *_desc_KeyfileUnreadable = "KeyfileUnreadable exception thrown";

		KeyfileUnreadable::KeyfileUnreadable(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_KeyfileUnreadable);
#endif
			description = (char *)_desc_KeyfileUnreadable;
		}
	};
};
