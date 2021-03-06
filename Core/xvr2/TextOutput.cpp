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
#include "TextOutput.h"
#include "MessageStrings.h"
#include<iostream>
#include<cstdio>

namespace xvr2{

	//static const char __ENDOFLINE[] = { '\n' };

	TextOutput::TextOutput(){
	}

	TextOutput::~TextOutput(){;}

	void TextOutput::write(const void *text, UInt32 size){
		outputMethod(text, size);
	}

	void TextOutput::write(const String &text){
		outputMethod(text.toCharPtr(), text.size());
	}

	void TextOutput::writeLine(const void *text, UInt32 size){
		outputMethod(text, size);
		//outputMethod(__ENDOFLINE, 1);
		outputMethod(NL.toCharPtr(), NL.size());
	}

	void TextOutput::writeLine(const String &text){
		outputMethod(text.toCharPtr(), text.size());
		outputMethod(NL.toCharPtr(), NL.size());
	}

	void TextOutput::outputMethod(const void *buf, UInt32 size){
		std::cerr << __PRETTY_FUNCTION__ << ' ' << msgPleaseOverride << std::endl;
	}
}
