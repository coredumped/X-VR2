/*
 * $Id$
 */
#ifndef __XVR2_TOKENIZER_H__
#define __XVR2_TOKENIZER_H__
#include<xvr2/System.h>
#include<xvr2/String.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{

	/** 
	 * This utilitary class is used whenever you need to split a string
	 * into tokens iteratively
	 */
	class Tokenizer:public System{
		private:
			/** Reserved use */
			char *temp;
			/** Contains the string to be splitted */
			char *buffer;
			/** Is a pointer to the las token obtained */
			char *token;
			/** Stores the delimiter */
			char *delim;
			/** Stores a temporal copy of buffer as a String */
			String tstr;
			/** Flag to say if there are more tokens or not */
			bool _fin;
		protected:
			/** When called returns the next token in the string */
			char *cnext();
		public:
			/** This constructor takes two arguments:
			 * <b>string</b>: is the string to be splitted
			 * <b>delim</b>: the delimiter
			 */
			Tokenizer(char *string, char *delim) ;
			/** This constructor takes two arguments:
			 * <b>string</b>: is the string to be splitted
			 * <b>delim</b>: the delimiter
			 */
			Tokenizer(const String &string, const String &delim) ;
			/** This destructor takes charge of releasing all the memory 
			 * allocated by all the private members */
			~Tokenizer ();
			/** When called returns the next token in the string,
			 *  if there are not any more tokens, then this method will
			 *  throw a NoMoreTokens exception.*/
			const String &next();
			/** Call this method in order to know if there are any
			 *  more tokens to read */
			bool finished();
	};


}

#endif
