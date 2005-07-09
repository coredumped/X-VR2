/*
 * $Id$
 */
#include<xvr2/NoDataForReadingException.h>

namespace xvr2 {
	namespace Exception{
#ifndef USING_GCC3
		static const char *_local_class_name_NoDataForReading = "xvr2::Exception::NoDataForReading";
#endif
		static const char *_desc_NoDataForReading = "NoDataForReading exception thrown";

		NoDataForReading::NoDataForReading(){
#ifndef USING_GCC3
			setClassName((char *)_local_class_name_NoDataForReading);
#endif
			description = (char *)_desc_NoDataForReading;
		}
	};
};

