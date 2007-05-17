/*
 * $Id$
 */
#include<xvr2/Exception.h>
#ifndef __xvr2_RegexException_H__
#define __xvr2_RegexException_H__

namespace xvr2 {
	namespace Exception {
		/**
		 * \class RegexException
		 * \version $Revision$
		 * \brief Generic Regex exception
		 */
		class Regex:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Regex();
				Regex(int errx);
		};
	};
};
#endif

