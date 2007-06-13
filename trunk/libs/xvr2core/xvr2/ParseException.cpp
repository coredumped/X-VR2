/*
 * $Id$
 */
#include"config.h"
#include "ParseException.h"
#include "MessageStrings.h"

namespace xvr2 {
	ParseException::ParseException(){
		description = (char *)xvr2::excepParse;
	}


	DateParseException::DateParseException(){
		description = (char *)xvr2::excepDateParse;
	}


	TimeParseException::TimeParseException(){
		description = (char *)xvr2::excepTimeParse;
	}


	BitParseException::BitParseException(){
		description = (char *)xvr2::excepBitParse;
	}


	ByteParseException::ByteParseException(){
		description = (char *)xvr2::excepByteParse;
	}
};


