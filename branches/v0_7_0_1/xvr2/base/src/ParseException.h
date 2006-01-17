/*
 * $Id$
 */
#ifndef __XVR2_PARSE_EXCEPTION_H__
#define __XVR2_PARSE_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	namespace Exception{

		/** Generic parsing exception */
		class Parse:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Parse();
		};


		/** Unable to parse and obtain a Date from the current object */
		class DateParse:public Parse{
			public:
				/**
				 * Default constructor
				 */
				DateParse();
		};


		/** Unable to parse and obtain a Time instance from the current object */
		class TimeParse:public Parse{
			public:
				/**
				 * Default constructor
				 */
				TimeParse();
		};


		/** This exception is thrown whenever you try to parse bit from an undefined format string or a too hard to transform datatype */
		class BitParse:public Parse{
			public:
				/**
				 * Default constructor
				 */
				BitParse();
		};


		/** Unable to parse a byte from here, probably the data is smaller than a byte? */
		class ByteParse:public Parse{
			public:
				/**
				 * Default constructor
				 */
				ByteParse();
		};

	};
};


#endif

