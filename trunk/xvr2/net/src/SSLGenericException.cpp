/*
 * $Id$
 */
#include<xvr2/SSLGenericException.h>
#include<openssl/err.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_SSLGeneric = "xvr2::Exception::SSLGeneric";
#endif
		//static const char *_desc_SSLGeneric = "SSLGeneric exception thrown";

		SSLGeneric::SSLGeneric(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_SSLGeneric);
#endif
			//description = (char *)_desc_SSLGeneric;
			description = (char *)ERR_lib_error_string(ERR_get_error());
		}
	};
};
