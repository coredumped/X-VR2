/*
 * $Id$
 */
#include<xvr2/NotConnectedException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_NotConnected = "xvr2::Exception::NotConnected";
#endif
		static const char *_desc_NotConnected = "NotConnected exception thrown";

		NotConnected::NotConnected(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_NotConnected);
#endif
			description = (char *)_desc_NotConnected;
		}
	};
};

