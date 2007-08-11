/*
 * $Id$
 */
#ifndef __XVR2_PARSE_EXCEPTION_H__
#define __XVR2_PARSE_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	/** Generic parsing exception */
	class ParseException:public Exception{
		public:
			/**
			 * Default constructor
			 */
			ParseException();
	};


	/** Unable to parse and obtain a Date from the current object */
	class DateParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			DateParseException();
	};


	/** Unable to parse and obtain a Time instance from the current object */
	class TimeParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			TimeParseException();
	};


	/** This exception is thrown whenever you try to parse bit from an undefined format string or a too hard to transform datatype */
	class BitParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			BitParseException();
	};


	/** Unable to parse a byte from here, probably the data is smaller than a byte? */
	class ByteParseException:public ParseException{
		public:
			/**
			 * Default constructor
			 */
			ByteParseException();
	};
};


#endif

