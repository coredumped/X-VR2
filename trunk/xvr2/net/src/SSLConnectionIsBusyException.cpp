/*
 * $Id$
 */
#include<xvr2/SSLConnectionIsBusyException.h>

namespace xvr2 {
	namespace Exception{
#if GCC_MAJOR_VERSION < 3
		static const char *_local_class_name_SSLConnectionIsBusy = "xvr2::Exception::SSLConnectionIsBusy";
#endif
		static const char *_desc_SSLConnectionIsBusy = "The read/write operation was not completed, try again later";

		SSLConnectionIsBusy::SSLConnectionIsBusy(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)_local_class_name_SSLConnectionIsBusy);
#endif
			description = (char *)_desc_SSLConnectionIsBusy;
		}
	};
};

