/*
 * $Id$
 */
#include<TextOutput.h>
#include<MessageStrings.h>
#include<iostream>
#include<cstdio>

namespace xvr2{

	static const char __ENDOFLINE[] = { '\n' };

	TextOutput::TextOutput(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2TextOutput);
#endif
	}

	TextOutput::~TextOutput(){;}

	void TextOutput::write(const void *text, UInt32 size){
		outputMethod(text, size);
	}

	void TextOutput::write(const String &text){
		String *g;
		g = (String *)&text;
		outputMethod(g->toCharPtr(), g->size());
	}

	void TextOutput::writeLine(const void *text, UInt32 size){
		outputMethod(text, size);
		outputMethod(__ENDOFLINE, 1);
	}

	void TextOutput::writeLine(const String &text){
		String *g;
		g = (String *)&text;
		outputMethod(g->toCharPtr(), g->size());
		outputMethod(__ENDOFLINE, 1);
	}

	void TextOutput::outputMethod(const void *buf, UInt32 size){
		std::cerr << __PRETTY_FUNCTION__ << ' ' << msgPleaseOverride << std::endl;
	}
#ifdef USE_DEBUG
	__xvr2_DebugOutput::__xvr2_DebugOutput(bool rf){
#ifndef USING_GCC3
		setClassName(_xvr2__xvr2_DebugOutput);
#endif
		redirect_to_file = rf;
	}
	
	void __xvr2_DebugOutput::outputMethod(const void *buf, UInt32 siz){
		if(redirect_to_file){
			FILE *fptr;
			fptr = fopen("xvr2-debug.log", "a");
			fwrite(buf, 1, siz, fptr);
			fclose(fptr);
		}
		else{
			std::cout << (char *)buf;
			std::cout.flush();
		}
	}
#endif
};

