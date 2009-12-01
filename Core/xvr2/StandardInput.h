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
#ifndef __XVR2_STANDARD_INPUT_H__
#define __XVR2_STANDARD_INPUT_H__
#include<xvr2/TextInput.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{

	/**
	 * This class represents the standard input stream as a 
	 * TextInput object
	 * @todo See if we can express the StandardInput class in terms of the new
	 * stream classes
	 */
	class StandardInput:public TextInput{
		protected:
			/**
			 * This is the overriden version of the
			 * input method on TextInput, basically
			 * it takes all its input desde el stdin
			 */
			virtual void inputMethod(void *buf, UInt32 size);
		public:
			/**
			 * Default constructor, it does some initialization
			 */
			StandardInput();
			
	};

}

#endif
