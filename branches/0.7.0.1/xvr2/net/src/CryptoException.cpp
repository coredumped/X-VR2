/*
 * $Id$
 */
#include"xvr2/CryptoException.h"

namespace xvr2 {
	namespace Exception{
#if __GNUC__ < 3
		static const char *_local_class_name_Crypto = "xvr2::Exception::Crypto";
#endif
		static const char *_desc_Crypto = "Crypto exception thrown";

		Crypto::Crypto(){
#if __GNUC__ < 3
			setClassName((char *)_local_class_name_Crypto);
#endif
			description = (char *)_desc_Crypto;
		}
	};
};

