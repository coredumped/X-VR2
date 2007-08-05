/*
 * $Id$
 */
#ifndef __NO_MORE_TOKENS_EXCEPTION_H__
#define __NO_MORE_TOKENS_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2{
	/**
	 * Use or trap this exception when you need to check if ha Tokenizer has no more tokens to
	 * find in the current string
	 */
	class NoMoreTokens:public Exception{
		public:
			/**
			 * Default constructor
			 */
			NoMoreTokens();
	};
};


#endif
