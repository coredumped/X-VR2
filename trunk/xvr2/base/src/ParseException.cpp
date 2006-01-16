/*
 * $Id$
 */
#include<xvr2/ParseException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Parse::Parse(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ParseException);
#endif
			description = (char *)xvr2::excepParse;
		}


		DateParse::DateParse(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DateParseException);
#endif
			description = (char *)xvr2::excepDateParse;
		}


		TimeParse::TimeParse(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2TimeParseException);
#endif
			description = (char *)xvr2::excepTimeParse;
		}


		BitParse::BitParse(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2BitParseException);
#endif
			description = (char *)xvr2::excepBitParse;
		}


		ByteParse::ByteParse(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ByteParseException);
#endif
			description = (char *)xvr2::excepByteParse;
		}

	};
};


