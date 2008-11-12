/*
 * $Id$
 */
#include"config.h"
#include "TextInput.h"
#include "MessageStrings.h"
#if __GNUC__ >= 3
#include<iostream>
#include<string>
#else
#include<iostream.h>
#endif
#if ((__GLIBC__ == 2) && (__GLIBC_MINOR__ > 7))
#include<cstring>
#else
#include<string>
#endif

namespace xvr2{

	TextInput::TextInput(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2TextInput);
#endif
	}

	TextInput::~TextInput(){;}

	void TextInput::read(void *buf, UInt32 size){
		inputMethod(buf, size);
	}

	void TextInput::readLine(char **buf, UInt32 *size){
		String buffer;
		char c;
		while(true){
			inputMethod(&c, 1);
			buffer.concat(c);
			if(c == '\0' && c == '\n'){
				break;
			}
		}
		*size = buffer.size();
		*buf = strdup(buffer.toCharPtr());
	}

	void TextInput::readLine(String &s){
		s.deleteString();
		char c, c2[2];
		c2[1] = 0;
		while(true){
			inputMethod(&c, 1);
			c2[0] = c;
			s.concat(c2);
			if(c == '\0' || c == '\n'){
				break;
			}
		}
	}

	void TextInput::inputMethod(void *buf, UInt32 size){
		std::cerr << __PRETTY_FUNCTION__ << ' ' << msgPleaseOverride << std::endl;
	}

};
