/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_STRING_EXCEPTION_H__
#define __XVR2_STRING_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	/** Generic String exception.
	 *  @todo Eliminate the Stringe class */
	class Stringe:public Exception{
		public:
			/**
			 * Default constructor
			 */
			Stringe();
	};
};


#endif

