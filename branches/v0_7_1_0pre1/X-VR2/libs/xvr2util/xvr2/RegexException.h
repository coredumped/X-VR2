/*
 * $Id$
 */
#include<xvr2/Exception.h>
#ifndef __xvr2_RegexException_H__
#define __xvr2_RegexException_H__

namespace xvr2 {
	namespace Util {
		/**
		 * \class RegexException
		 * \version $Revision$
		 * \brief Generic Regex exception
		 */
		class RegexException:public Exception{
			public:
				/**
				 * Default constructor
				 */
				RegexException();
				RegexException(int errx);
		};
	};
};
#endif
