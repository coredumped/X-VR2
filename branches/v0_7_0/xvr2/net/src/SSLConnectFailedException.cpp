/*
 * $Id$
 */
#include<xvr2/SSLConnectFailedException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_SSLConnectFailed = "xvr2::Exception::SSLConnectFailed";
#endif
		static const char *_desc_SSLConnectFailed = "SSLConnectFailed exception thrown";

		SSLConnectFailed::SSLConnectFailed(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_SSLConnectFailed);
#endif
			description = (char *)_desc_SSLConnectFailed;
		}
	};
};

