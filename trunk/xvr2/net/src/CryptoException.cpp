/*
 * $Id$
 */
#include"xvr2/CryptoException.h"

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_Crypto = "xvr2::Exception::Crypto";
#endif
		static const char *_desc_Crypto = "Crypto exception thrown";

		Crypto::Crypto(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_Crypto);
#endif
			description = (char *)_desc_Crypto;
		}
	};
};

