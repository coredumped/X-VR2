/*
 * $Id$
 */
#include"config.h"
#include "ParseException.h"
#include "MessageStrings.h"

namespace xvr2 {
	ParseException::ParseException(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ParseException);
#endif
		description = (char *)xvr2::excepParse;
	}


	DateParseException::DateParseException(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2DateParseException);
#endif
		description = (char *)xvr2::excepDateParse;
	}


	TimeParseException::TimeParseException(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2TimeParseException);
#endif
		description = (char *)xvr2::excepTimeParse;
	}


	BitParseException::BitParseException(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2BitParseException);
#endif
		description = (char *)xvr2::excepBitParse;
	}


	ByteParseException::ByteParseException(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ByteParseException);
#endif
		description = (char *)xvr2::excepByteParse;
	}
};


