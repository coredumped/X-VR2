/*
 * $Id$
 */
#ifndef __XVR2_STANDARD_INPUT_H__
#define __XVR2_STANDARD_INPUT_H__
#include<TextInput.h>

namespace xvr2{

	/**
	 * This class represents the standard input stream as a 
	 * TextInput object
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

};

#endif
