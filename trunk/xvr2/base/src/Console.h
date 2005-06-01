/*
 * $Id$
 */
#ifndef __XVR2_CONSOLE_H__
#define __XVR2_CONSOLE_H__
#include<xvr2/Unix.h>
#include<xvr2/TextOutput.h>
#include<xvr2/TextInput.h>
#include<xvr2/NullPointerException.h>

namespace xvr2{
	
	/**
	 * This class represents the console object, use to retreive
	 * and send data to the current Unix console
	 */
	class Console:public Unix{
		protected:
			/** This will represent the stderr */
			TextOutput *err;
			/** This will represent the stdout */
			TextOutput *out;
			/** This will represent the stdin */
			TextInput  *in;
			/** This flag will say if you are using the 
			 *  builtin TextOutput object or a 
			 *  user-defined one for stdout*/
			bool using_builtin_out;
			/** This flag will say if you are using the 
			 *  builtin TextOutput object or a 
			 *  user-defined one for stderr*/
			bool using_builtin_err;
			/** This flag will say if you are using the 
			 *  builtin TextInput object or a 
			 *  user-defined one for stdin*/
			bool using_builtin_in;
		public:
			/** Default constructor, this will set
			 *  the standard output TextOutput to 
			 *  stdout, standard error TextOutput to 
			 *  stderr */
			Console();
			/** If you didnt changed the output and error
			 *  TextOuputs then this destructor will 
			 *  clear the references to <b>out</b> 
			 *  and <b>err</b>*/
			~Console();
			/** This will reset the standard output to
			 *  stdout by default or to <b>to</b> */
			void setOutput(TextOutput *to = 0);
			/** This will reset the standard input to
			 *  stdin by default or to <b>ti</b> */
			void setInput(TextInput *ti = 0);
			/** This will reset the standard error to
			 *  stderr by default or to <b>te</b> */
			void setErrorOutput(TextOutput *te = 0);
			/** This will write <b>siz</b> bytes of 
			 *  <b>buf</b> buffer to the current out 
			 *  TextOutput */
			void outWrite(const void *buf, UInt32 siz);
			/**
			 * This will write the contents of <b>text</b>
			 * to the current out TextOutput */
			void outWrite(const String &text);
			/** This will write <b>siz</b> bytes of 
			 *  <b>buf</b> buffer to the current out 
			 *  TextOutput plus a newline character*/
			void outWriteLine(const void *buf, UInt32 siz);
			/** This will write the contents of 
			 *  <b>text</b> to the current out 
			 *  TextOutput plus a  newline */
			void outWriteLine(const String &text);
			/** This will write <b>siz</b> bytes of 
			 *  <b>buf</b> buffer to the current err 
			 *  TextOutput */
			void errWrite(const void *buf, UInt32 siz);
			/** This will write the contents of <b>text</b>
			 *  to the current err TextOutput */
			void errWrite(const String &text);
			/** This will write <b>siz</b> bytes of 
			 *  <b>buf</b> buffer to the current err 
			 *  TextOutput plus a newline character*/
			void errWriteLine(const void *buf, UInt32 siz);
			/** This will write the contents of <b>text</b>
			 *  to the current err TextOutput plus a 
			 *  newline */
			void errWriteLine(const String &text);
			/** This will read <b>size</b> bytes from 
			 *  the current <b>in</b> and will store
			 *  them on <b>buf</b> */
			void read(void *buf, UInt32 size);
			/** This will read a line of text, a line
			 *  is a string terminated by \\n or \\0
			 *  the result will be stored on <b>line</b> */
			void readLine(String &line);
	};
#ifdef USE_DEBUG
	extern Console __debug_console;
#endif
};

#endif
