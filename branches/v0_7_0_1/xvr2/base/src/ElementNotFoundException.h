/*
 * $Id$
 */
#ifndef __ELEMENT_NOT_FOUND_EXCEPTION_H__
#define __ELEMENT_NOT_FOUND_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	namespace Exception{

		/**
		 * Use this exception when a search for an element returned no results or the results
		 * given doens't match what you were looking for
		 */
		class ElementNotFound:public Exception{
			public:
				/**
				 * Default constructor
				 */
				ElementNotFound();
		};

	};
};


#endif
