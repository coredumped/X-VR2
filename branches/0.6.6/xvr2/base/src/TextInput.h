/*
 * $Id$
 */
#ifndef __XVR2_TEXT_INPUT_H__
#define __XVR2_TEXT_INPUT_H__
#include<System.h>
#include<String.h>

namespace xvr2{

	/** This class is like a PIPE, it holds a method for 
	 *  inputing text from an object, this object \
	 *  can be a file a stream or any other thing, please
	 *  note that this class is just an interface, for 
	 *  every text input subsystem that may exist in a 
	 *  future
	 *
	 */
	class TextInput:protected System{
		protected:
			virtual void inputMethod(void *buf, UInt32 size);
		public:
			TextInput();
			virtual ~TextInput();

			void read(void *buf, UInt32 size);
			virtual void readLine(char **buf, UInt32 *size);
			virtual void readLine(String &s);
	};
};

#endif

