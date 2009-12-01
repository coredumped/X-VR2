/*
 * $Id$
 */
#include<xvr2/UDPReceiveTimeoutException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_UDPReceiveTimeout = "xvr2::Exception::UDPReceiveTimeout";
#endif
		static const char *_desc_UDPReceiveTimeout = "UDPReceiveTimeout exception thrown";

		UDPReceiveTimeout::UDPReceiveTimeout(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_UDPReceiveTimeout);
#endif
			description = (char *)_desc_UDPReceiveTimeout;
		}
	};
};

