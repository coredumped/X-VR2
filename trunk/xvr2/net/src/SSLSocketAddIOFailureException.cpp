/*
 * $Id$
 */
#include<xvr2/SSLSocketAddIOFailureException.h>

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_SSLSocketAddIOFailure = "xvr2::Exception::SSLSocketAddIOFailure";
#endif
		static const char *_desc_SSLSocketAddIOFailure = "SSLSocketAddIOFailure exception thrown";

		SSLSocketAddIOFailure::SSLSocketAddIOFailure(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_SSLSocketAddIOFailure);
#endif
			description = (char *)_desc_SSLSocketAddIOFailure;
		}
	};
};

