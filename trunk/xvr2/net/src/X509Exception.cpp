/*
 * $Id$
 */
#include<xvr2/X509Exception.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_X509 = "xvr2::Exception::X509";
#endif
		static const char *_desc_X509 = "X509 exception thrown";

		X509::X509(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_X509);
#endif
			description = (char *)_desc_X509;
		}
	};
};

