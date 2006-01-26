/*
 * $Id$
 */
#include"config.h"
#include "TextOutput.h"
#include "MessageStrings.h"
#include<iostream>
#include<cstdio>

namespace xvr2{

	static const char __ENDOFLINE[] = { '\n' };

	TextOutput::TextOutput(){
#if USE_EMBEDDED_CLASSNAMES
		setClassName(xvr2::_xvr2TextOutput);
#endif
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
		outputMethod(__ENDOFLINE, 1);
	}

	void TextOutput::writeLine(const String &text){
		outputMethod(text.toCharPtr(), text.size());
		outputMethod(__ENDOFLINE, 1);
	}

	void TextOutput::outputMethod(const void *buf, UInt32 size){
		std::cerr << __PRETTY_FUNCTION__ << ' ' << msgPleaseOverride << std::endl;
	}
};
