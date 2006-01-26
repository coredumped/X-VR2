/*
 * $Id$
 */
#ifndef __XVR2_TEXT_OUTPUT_H__
#define __XVR2_TEXT_OUTPUT_H__
#include<xvr2/System.h>
#include<xvr2/String.h>

namespace xvr2{
	/** This class is like a PIPE, it holds a method for 
	 *  outputing text to a receiving object, this object \
	 *  can be a file a stream or any other thing, please
	 *  note that this class is just an interface, for 
	 *  every text ouput subsystem that may exist in a 
	 *  future
	 */
	class TextOutput:protected System{
		protected:
			/**
			 * This is the current output method, it will
			 * determine how the data is going to be 
			 * phisically outputed, you are encouraged
			 * to overload this method in every 
			 * implementation of the <b>TextOutput</b> class */
			virtual void outputMethod(const void *buf, UInt32 size);
		public:
			/** Default constructor, it does some local initialization but nothing more */
			TextOutput();
			virtual ~TextOutput();
			/** This method will write the <b>text</b>buffer up to <b>siz</b> bytes to the current TextOuput object */
			void write(const void *text, UInt32 siz);
			/** This method will write the <b>text</b> String to the current TextOuput object */
			void write(const String &text);
			/** This method will write the <b>text</b>buffer up to <b>siz</b> bytes to the current TextOuput object plus the newline character*/
			void writeLine(const void *text, UInt32 siz);
			/** This method will write the <b>text</b> String to the current TextOuput object plus the newline character*/
			void writeLine(const String &text);
	};

};

#endif
