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
#include"config.h"
#include "TextInput.h"
#include "MessageStrings.h"
#if __GNUC__ >= 3
#include<iostream>
#include<string>
#else
#include<iostream.h>
#include<string.h>
#endif

namespace xvr2{

	TextInput::TextInput(){
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

}
