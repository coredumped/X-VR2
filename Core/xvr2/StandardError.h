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
#ifndef __XVR2_STANDARD_ERROR_H__
#define __XVR2_STANDARD_ERROR_H__
#include<xvr2/TextOutput.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	/** This class represents the Standard Error output stream */
	class StandardError:public TextOutput{
		protected:
			void outputMethod(const void *buff, UInt32 size);
		public:
			StandardError();
	};
}

#endif
