/*
 * $Id$
 */
#include<xvr2/SSLConnectFailedException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_SSLConnectFailed = "xvr2::Exception::SSLConnectFailed";
#endif
		static const char *_desc_SSLConnectFailed = "SSLConnectFailed exception thrown";

		SSLConnectFailed::SSLConnectFailed(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_SSLConnectFailed);
#endif
			description = (char *)_desc_SSLConnectFailed;
		}
	};
};

