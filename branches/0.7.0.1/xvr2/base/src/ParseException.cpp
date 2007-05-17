/*
 * $Id$
 */
#include<xvr2/ParseException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Parse::Parse(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2ParseException);
#endif
			description = (char *)xvr2::excepParse;
		}


		DateParse::DateParse(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2DateParseException);
#endif
			description = (char *)xvr2::excepDateParse;
		}


		TimeParse::TimeParse(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2TimeParseException);
#endif
			description = (char *)xvr2::excepTimeParse;
		}


		BitParse::BitParse(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2BitParseException);
#endif
			description = (char *)xvr2::excepBitParse;
		}


		ByteParse::ByteParse(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2ByteParseException);
#endif
			description = (char *)xvr2::excepByteParse;
		}

	};
};


