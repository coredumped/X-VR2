/*
 * $Id$
 */
#include<xvr2/SSLContextCreationException.h>
#include<openssl/err.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_SSLContextCreation = "xvr2::Exception::SSLContextCreation";
#endif
		//static const char *_desc_SSLContextCreation = "SSLContextCreation exception thrown";

		SSLContextCreation::SSLContextCreation(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_SSLContextCreation);
#endif
			//description = _desc_SSLContextCreation;
			description = (char *)ERR_lib_error_string(ERR_get_error());
#ifdef USE_DEBUG
			debugmsgln(this, description);
#endif
		}
	};
};

