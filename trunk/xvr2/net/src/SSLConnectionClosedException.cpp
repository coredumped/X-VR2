/*
 * $Id$
 */
#include<xvr2/SSLConnectionClosedException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_SSLConnectionClosed = "xvr2::Exception::SSLConnectionClosed";
#endif
		static const char *_desc_SSLConnectionClosed = "SSLConnectionClosed exception thrown";

		SSLConnectionClosed::SSLConnectionClosed(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_SSLConnectionClosed);
#endif
			description = (char *)_desc_SSLConnectionClosed;
		}
	};
};

