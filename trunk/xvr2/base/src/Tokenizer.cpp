/*
 * $Id$
 */
#include<xvr2/Tokenizer.h>
#include<xvr2/Exception.h>
#include<xvr2/_xvr2ClassNames.h>
#include<string.h>
#include<stdlib.h>

namespace xvr2{

	Tokenizer::Tokenizer(char *phrase, char *d){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Tokenizer);
#endif
		temp = 0;
		token = 0;
		_fin = false;
		buffer = strdup(phrase);
		temp = strdup(phrase);
		delim = strdup(d);
	}

	Tokenizer::Tokenizer(const String &phrase, const String &d){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Tokenizer);
#endif
		temp = 0;
		token = 0;
		_fin = false;
		buffer = strdup(phrase.toCharPtr());
		temp = strdup(phrase.toCharPtr());
		delim = strdup(d.toCharPtr());
	}

	Tokenizer::~Tokenizer(){
		if(temp != 0)
			free(temp);
		if(buffer != 0)
			free(buffer);
		if(token != 0)
			free(token);
		if(delim != 0)
			free(delim);
	}

	bool Tokenizer::finished(){
		return _fin;
	}

	char *Tokenizer::cnext(){
		unsigned int i;
		unsigned int len;
		char *ptr, *tptr;;
		if(buffer == 0){
			_fin = true;
			return 0;
		}
		if(strstr(buffer, delim) == 0){
				if(token == 0)
					token = strdup(buffer);
				free(buffer);
				buffer = 0;
				_fin = true;
				return token;
		}
		if(temp == 0){
			free(token);
			token = 0;
			free(buffer);
			buffer = 0;
			free(delim);
			delim = 0;
			_fin = true;
			return 0;
		}
		else{
			if(token != 0){
				free(token);
				token = 0;
			}
			if((ptr = strstr(temp, delim)) == 0){
				token = strdup(temp);
				free(temp);
				temp = 0;
				_fin = true;
			}
			else{
				token = (char *)malloc(strlen(temp) * sizeof(char));
				memset((void *)token, 0, strlen(temp));
				len = (((unsigned int)ptr)- (unsigned int)temp);
				for(i = 0; i < len; i++){
					token[i] = temp[i];
				}
				token[i] = 0;
				tptr = strdup(ptr + strlen(delim));
				free(temp);
				temp = tptr;
			}
		}
		return token;
	}

	const String &Tokenizer::next(){
		char *ptr;
		ptr = cnext();
		if(ptr == 0){
			throw Exception::NoMoreTokens();
			//return 0;
		}
		tstr = ptr;
		return tstr;
	}

};
