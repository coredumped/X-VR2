/*
 * $Id$
 */
#include<xvr2/UDPReceiveTimeoutException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_UDPReceiveTimeout = "xvr2::Exception::UDPReceiveTimeout";
#endif
		static const char *_desc_UDPReceiveTimeout = "UDPReceiveTimeout exception thrown";

		UDPReceiveTimeout::UDPReceiveTimeout(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_UDPReceiveTimeout);
#endif
			description = (char *)_desc_UDPReceiveTimeout;
		}
	};
};

