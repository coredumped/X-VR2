/*
 * $Id$
 */
#include<xvr2/NoValidCipherInListException.h>

namespace xvr2 {
	namespace Exception{
#if GCC_MAJOR_VERSION < 3
		static const char *_local_class_name_NoValidCipherInList = "xvr2::Exception::NoValidCipherInList";
#endif
		static const char *_desc_NoValidCipherInList = "NoValidCipherInList exception thrown";

		NoValidCipherInList::NoValidCipherInList(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)_local_class_name_NoValidCipherInList);
#endif
			description = (char *)_desc_NoValidCipherInList;
		}
	};
};

