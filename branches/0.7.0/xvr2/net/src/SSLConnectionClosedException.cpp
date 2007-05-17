/*
 * $Id$
 */
#include<xvr2/SSLConnectionClosedException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_SSLConnectionClosed = "xvr2::Exception::SSLConnectionClosed";
#endif
		static const char *_desc_SSLConnectionClosed = "SSLConnectionClosed exception thrown";

		SSLConnectionClosed::SSLConnectionClosed(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_SSLConnectionClosed);
#endif
			description = (char *)_desc_SSLConnectionClosed;
		}
	};
};

