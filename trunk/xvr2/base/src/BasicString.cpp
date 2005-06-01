/*
 * $Id$
 */
#define __XVR2_ENABLE_BASIC_STRING__
#include"xvr2/BasicString.h"

namespace xvr2 {
	CharString::CharString(const CharString &s){
		assign(s.buffer);
	}
	CharString::CharString(const char *s){
		assign(s);
	}

	const CharString &CharString::operator=(const CharString &s){
		assign(s.buffer);
		return *this;
	}
	const CharString &CharString::operator=(const char *s){
		assign(s);
		return *this;
	}
};
