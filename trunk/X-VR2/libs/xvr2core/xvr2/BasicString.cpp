/*
 * $Id$
 */
#define __XVR2_ENABLE_BASIC_STRING__
#include"config.h"
#include"BasicString.h"

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
	int CharString::index(const char *s, const int start) const{
		int i, j;
		if(len == 0 || s == 0)
			return -1;
		else if(s[0] == 0) return -1;
		for(i = start; i < len; i++){
			if(buffer[i] == s[0]){
				for(j = 0; buffer[i + j] != 0; j++){
					if(buffer[i + j] != s[j])
						continue;
				}
				return i;
			}
		}
		return -1;
	}
	int CharString::rindex(const char *s, int end) const{
		int i, j, ssize, e;
		bool is_ok = true;
		if(len == 0 || s == 0) return -1;
		else{
		       	if(s[0] == 0) return -1;
		}
		ssize = getlen(s);
		if(end == 0)
			//e = len - 1 - ssize;
			e = len - ssize;
		else{
			if(end > (len - ssize))
				return -1;
			else
				e = end;
		}
		for(i = e; i >= 0; i--){
			if(buffer[i] == s[0]){
				for(j = 0; j < ssize - 1; j++){
					if(charAt(i + j) != s[j]){
						is_ok = false;
						break;
					}
				}
				if(is_ok)
					return len - (i + j + 1);
			}
		}
		return -1;
	}
};
