/*
 $Id$
 */
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<_xvr2ClassNames.h>
#include<String.h>
#include<ArrayIndexOutOfLimitsException.h>
#include<NumberException.h>
#include<NullPointerException.h>
#include<ctype.h>
#ifdef USING_GCC3
#include<iostream>
#include<string>
#else
#include<iostream.h>
#include<string.h>
#endif
#include<errno.h>
#include<Memory.h>
#ifdef HAVE_POW
#include<math.h>
#endif

namespace xvr2{

	int __str_shrink(char **buf){
		char *tmp;
		int n, i;
		if(*buf == 0)
			return 0;
		n = strlen(*buf);
		tmp = new char[n + 1];
		for(i = 0; i < n; i++)
			tmp[i] = *buf[i];
		tmp[n] = 0;
		xvr2_delete_array(buf);
		*buf = tmp;
		return n;
	}
	
	void int2char(int num, char buf[]){
		sprintf(buf, "%d", num);
		return;
		float tmp;
		int dec;
		int idx = 0;
		unsigned int flat;
		if(num < 0){
			buf[idx++] = '-';
			num = num * -1;
		}
		while(num != 0){
			tmp = num / 10.0;
			flat = num / 10;
			dec = (int)((tmp - (float)flat) * 10);
			buf[idx++] = dec + '0';
			num = num / 10;
		}
		buf[idx] = 0;
	}
	
	char *String::toCharPtr() const {
		if(this == 0x0)
			throw Exception::NullPointer();
		return buffer;
	}
	
	String::~String(){
		destroy();
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
		debugmsg(this, " String::~String()\n");
	#endif
#endif
	}
	
	String::String(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
	}
	
	String::String(String &s){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(s.buffer);
	}
	
	String::String(const char *s){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(s);
	}
	
	String::String(const int n){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(n);
	}
	
	String::String(const unsigned int n){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(n);
	}
	
	String::String(const float n){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(n);
	}
	
	String::String(const double n){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(n);
	}
	
	String::String(const long double n){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(n);
	}
	
	String::String(const Int64 n){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		buffer = 0;
		len = 0;
		assign(n);
	}
	
	
	void String::destroy(){
#ifndef USING_GCC3
		//Under GCC3 and C99 compliant compiler you can safely free
		//an already freed pointer
		if(buffer == 0 || len == 0)
			return;
#endif
		xvr2_delete_array(buffer);
		len = 0;
	}
	
	void String::assign(const char *s){
		//int n;
		if(s == 0)
			return;
		/*if(s[0] == 0)
			return;*/
		destroy();
		len = strlen(s);
		//len = n;
		buffer = new char[len + 1];
		/*for(n = 0; n < len; n++){
			buffer[n] = s[n];
		}
		buffer[n] = 0;*/
		Memory::copy((void *)buffer, (void *)s, len + 1);
		//buffer[len = 0];
	}
	
	void String::assign(const int n){
		char num[14];
		//num = new char[14];
		int2char(n, num);
		assign(num);
		//xvr2_delete_array(num);
	}
	
	void String::assign(const unsigned int n){
		char num[14];
		/*char *num = 0;
		num = new char[13];*/
		sprintf(num, "%u", n);
		assign(num);
		//xvr2_delete_array(num);
	}
	
	void String::assign(const float n){
		char num[80];
		/*char *num = 0;
		num = new char[80];*/
		sprintf(num, "%f", n);
		assign(num);
		//xvr2_delete_array(num);
	}
	
	void String::assign(const double n){
		char num[80];
		/*char *num = 0;
		num = new char[80];*/
		sprintf(num, "%f", n);
		assign(num);
		//xvr2_delete_array(num);
	}
	
	void String::assign(const long double n){
		char num[256];
		/*char *num = 0;
		num = new char[256];*/
		sprintf(num, "%Lf", n);
		assign(num);
		//xvr2_delete_array(num);
	}
	
	void String::assign(const Int64 n){
		char num[32];
		/*char *num = 0;
		num = new char[32];*/
		sprintf(num, "%lld", n);
		assign(num);
		//xvr2_delete_array(num);
	}

	void String::assign(const String &sstr){
		assign(((String *)&sstr)->toCharPtr());
	}
	
	void String::concat(const char *s){
		int len_s;
		char *tmp;
		if(s == 0)
			return;
		else
			if(s[0] == 0)
				return;
		if(buffer == 0){
			assign(s);
			return;
		}
		len_s = strlen(s);
		tmp = new char[len + len_s + 1];
		/*for(i = 0; i < len; i++){
			tmp[i] = buffer[i];
		}
		for(j = 0; j < len_s; j++, i++){
			tmp[i] = s[j];
		}
		tmp[i] = 0;*/
		tmp[0] = 0;
		strcat(tmp, buffer);
		xvr2_delete_array(buffer);
		strcat(tmp, s);
		assign(tmp);
		xvr2_delete_array(tmp);
	}
	
	void String::concat(String &s){
		concat(s.buffer);
	}
	
	void String::concat(const int n){
		char *buf;
		buf = new char[14];
		int2char(n, buf);
		concat(buf);
		xvr2_delete_array(buf);
	}
	
	void String::concat(const unsigned int n){
		char *buf;
		buf = new char[14];
		sprintf(buf, "%u", n);
		concat(buf);
		xvr2_delete_array(buf);
	}
	
	void String::concat(const float n){
		char *buf;
		buf = new char[256];
		sprintf(buf, "%f", n);
		concat(buf);
		xvr2_delete_array(buf);
	}
	
	void String::concat(const double n){
		char *buf;
		buf = new char[256];
		sprintf(buf, "%f", n);
		concat(buf);
		xvr2_delete_array(buf);
	}
	
	void String::concat(const long double n){
		char *buf;
		buf = new char[256];
		sprintf(buf, "%Lf", n);
		concat(buf);
		xvr2_delete_array(buf);
	}
	
	void String::concat(const Int64 n){
		char *buf;
		buf = new char[25];
		sprintf(buf, "%lld", n);
		concat(buf);
		xvr2_delete_array(buf);
	}
	
	void String::concat(const UInt64 n){
		char *buf;
		buf = new char[25];
		sprintf(buf, "%llu", n);
		concat(buf);
		xvr2_delete_array(buf);
	}

	void String::concat(const char c){
		char cc[2];
		cc[0] = c;
		cc[1] = 0;
		concat(cc);
	}
	
	String& String::operator=(const char *s){
		assign(s);
		return *this;
	}
	
	/*String& String::operator=(String &s){
		assign(s.toCharPtr());
		return *this;
	}*/
	
	String& String::operator=(const int n){
		assign(n);
		return *this;
	}
	
	String& String::operator=(const unsigned int n){
		assign(n);
		return *this;
	}
	
	String& String::operator=(const float n){
			assign(n);
		return *this;
	}
	
	String& String::operator=(const double n){
		assign(n);
		return *this;
	}
	
	String& String::operator=(const long double n){
		assign(n);
		return *this;
	}
	
	String& String::operator=(const Int64 n){
		assign(n);
		return *this;
	}
	
	String& String::operator+(String &s){
		concat(s);
		return *this;
	}
	
	String& String::operator+(const char *s){
		concat(s);
		return *this;
	}
	
	String& String::operator+(const int n){
		concat(n);
		return *this;
	}
	
	String& String::operator+(const unsigned int n){
		concat(n);
		return *this;
	}
	
	String& String::operator+(const float n){
		concat(n);
		return *this;
	}
	
	String& String::operator+(const double n){
		concat(n);
		return *this;
	}
	
	String& String::operator+(const long double n){
		concat(n);
		return *this;
	}
	
	String& String::operator+(const Int64 n){
		concat(n);
		return *this;
	}
	
	String& String::operator+(const UInt64 n){
		concat(n);
		return *this;
	}
	
	String& String::operator+=(String &s){
		concat(s);
		return *this;
	}
	
	String& String::operator+=(const char *s){
		concat(s);
		return *this;
	}
	
	String& String::operator+=(const int n){
		concat(n);
		return *this;
	}
	
	String& String::operator+=(const unsigned int n){
		concat(n);
		return *this;
	}
	
	String& String::operator+=(const float n){
		concat(n);
		return *this;
	}
	
	String& String::operator+=(const double n){
		concat(n);
		return *this;
	}
	
	String& String::operator+=(const long double n){
		concat(n);
		return *this;
	}
	
	String& String::operator+=(const Int64 n){
		concat(n);
		return *this;
	}
	
	String& String::operator+=(const UInt64 n){
		concat(n);
		return *this;
	}
	
	std::ostream& operator<<(std::ostream& stream, String s){
		stream << s.buffer;
		return stream;
	}
	
	const char String::charAt(int i){
		if(i < 0 || i >= len)
			throw Exception::ArrayIndexOutOfLimits();
		return buffer[i];
	}
	
	const char String::operator[](int i){
		return charAt(i);
	}
	
	void String::deleteString(){
	          destroy();
	}
	
	String &String::trimLeft(const char c){
		int i = 0;
#ifndef HAVE_STRCPY
		int j = 0;
#endif
		char *buf, *ptr;
		if(buffer == 0){
			throw Exception::NullPointer();
			return *this;
		}
		buf = new char[len + 1];
		ptr = buffer;
		while(*(ptr++) == c) 
			i++;
#ifdef HAVE_STRCPY
		strcpy(buf, ptr);
#else
		for(j = 0; buffer[i] != 0; j++, i++)
			buf[j] = buffer[i];
		buf[j] = 0;
#endif
		//destroy();
		assign(buf);
		xvr2_delete_array(buf);
		return *this;
	}
	
	
	String &String::trimRight(const char c){
		int i;
		if(buffer == 0){
			throw Exception::NullPointer();
			return *this;
		}
		for(i = len - 1; buffer[i] == c; i--)
			buffer[i] = 0;
		return *this;
	}
	
	String& String::trim(const char c){
		trimLeft(c);
		trimRight(c);
		return *this;
	}
	
	String& String::toUpperCase(){
		register int i;
		for(i = 0; i < len; i++){
			buffer[i] = toupper(buffer[i]);
		}
		return *this;
	}
	
	String& String::toLowerCase(){
		register int i;
		for(i = 0; i < len; i++){
			buffer[i] = tolower(buffer[i]);
		}
		return *this;
	}
	
	const unsigned int String::lenght(){
		return len;
	}
	
	const unsigned int String::size(){
		return len;
	}
	
	int __power(int n){
#ifdef HAVE_POW
		return (int)pow(10.0, (double)n);
#else
		int i, num = 1;
		for(i = 1; i <= n; i++){
			num = num * 10;
		}
		return num;
#endif
	}
	
	const int String::toInt(){
#ifdef HAVE_STRTOL
		int num = 0;
#endif
		if(buffer == 0)
			return 0;
		if(buffer[0] == 0)
			return 0;
#ifdef HAVE_STRTOL
		num = strtol(buffer, 0, 10);
		return num;
#else
		return atoi(buffer);
#endif
	}
	
	const unsigned int String::toUInt(){
		unsigned int num = 0, low = 0;
		unsigned int i, j;
		if(buffer == 0)
			return 0;
		if(buffer[0] == 0)
			return 0;
		if(buffer[0] == '+')
			low = 1;
		if(isdigit(buffer[0]) || buffer[0] == '+'){
			for(i = (len - 1), j = 0; i >= low; i--, j++){
				if(!isdigit(buffer[i])){
					throw Exception::Number();
				}
				num = num + (buffer[i] - '0')* __power(j);
			}
		}
		else
			if(buffer[0] != '+'){
				throw Exception::Number();
			}
		return num;
	}
	
	const float String::toFloat(){
		if(buffer == 0)
			return 0;
		if(buffer[0] == 0)
			return 0;
		return (float)toDouble();
	}
	
	const double String::toDouble(){
		if(buffer == 0)
			return 0;
		if(buffer[0] == 0)
			return 0;
		return atof(buffer);
	}
	
	const long double String::toLongDouble(){
		if(buffer == 0)
			return 0;
		if(buffer[0] == 0)
			return 0;
		return strtold(buffer, 0);
	}
	
	const Int64 String::toInt64(){
		if(buffer == 0)
			return 0;
		if(buffer[0] == 0)
			return 0;
		return atoll(buffer);
	}

	bool String::operator==(const String &s){
		return equals(s);
	}
	
	bool String::operator==(const char *s){
		return equals(s);
	}
	
	bool String::operator==(const int n){
		return equals(n);
	}
	bool String::operator==(const unsigned int n){
		return equals(n);
	}
	
	bool String::operator==(const float n){
		return equals(n);
	}
	
	bool String::operator==(const double n){
		return equals(n);
	}
	
	bool String::operator==(const long double n){
		return equals(n);
	}
	
	bool String::operator==(const Int64 n){
		return equals(n);
	}
	
	/*bool String::equals(const String &s){
		unsigned int i;
		if(size() != ((String *)&s)->size())
			return false;
		for(i = 0; i < size(); i++)
			if(charAt(i) != ((String *)&s)->charAt(i))
				return false;
		return true;
	}*/
	
	bool String::equals(const char *s){
		/*unsigned int i;
		unsigned int siz;*/
		if(len == 0 && s == 0)
			return true;
		if(len == 0)
			return false;
		if(s == 0)
			return false;
		/*siz = strlen(s);
		if(size() != siz)
			return false;*/
		if(strcmp(buffer, s) == 0)
			return true;
		/*for(i = 0; i < size(); i++)
			if(charAt(i) != s[i])
				return false;*/
		return false;
	}
	
	bool String::equals(const String &s1){
		return equals(((String *)&s1)->toCharPtr());
	}
	
	bool String::equals(const String &s1, const String &s2){
		return ((String *)&s1)->equals(((String *)&s2)->toCharPtr());
	}
	
	bool String::equals(const int n){
		String s(n);
		return equals(s);
	}
	
	bool String::equals(const unsigned int n){
		String s(n);
		return equals(s);
	}
	
	bool String::equals(const float n){
		String s(n);
		return equals(s);
	}
	
	bool String::equals(const double n){
		String s(n);
		return equals(s);
	}
	
	bool String::equals(const long double n){
		String s(n);
		return equals(s);
	}
	
	bool String::equals(const Int64 n){
		String s(n);
		return equals(s);
	}
	
	bool String::hasSubstring(String &s){
		if(buffer == 0)
			return false;
		else
			if(buffer[0] == 0)
				return false;
		if(strstr(buffer, s.toCharPtr()) == NULL)
			return false;
		return true;
	}
	
	bool String::hasSubstring(const char *s){
		if(buffer == 0)
			return false;
		else
			if(buffer[0] == 0)
				return false;
		if(strstr(buffer, s) == NULL)
			return false;
		return true;
	}
	
	String &String::deleteFirst(){
		unsigned int i;
		//Use this algorithm to favor no allocation of addional 
		//memory
		if(buffer == 0)
			return *this;
		else{
			if(buffer[0] == 0)
				return *this;
			else{
				if(size() == 1){
					destroy();
					return *this;
				}
			}
		}
		for(i = 1; i < size(); i++){
			buffer[i - 1] = buffer[i];
		}
		buffer[i - 1] = 0;
		len--;
		return *this;
	}
	
	String &String::deleteLast(){
		if(buffer == 0)
			return *this;
		else{
			if(buffer[0] == 0)
				return *this;
			if(size() == 1){
				destroy();
#ifdef USE_DEBUG
				debugmsg(this, "Destroyed\n");
#endif
				return *this;
			}
		}
		buffer[len - 1] = '\0';
		len--;
		return *this;
	}
	
	const int String::index(const String &s, int start){
		unsigned int i, j;
		if(size() == 0)
			return -1;
		if(((String *)&s)->size() == 0)
			return -1;
		for(i = start; i < size() - ((String *)&s)->size(); i++){
			if(charAt(i) == ((String *)&s)->charAt(0)){
				for(j = 0; j < ((String *)&s)->size(); j++){
					if(charAt(i + j) != ((String *)&s)->charAt(j))
						continue;
				}
				return i;
			}
		}
		return -1;
	}
	
	const int String::index(const char *s, int start){
		unsigned int i, j, ssize;
		if(size() == 0)
			return -1;
		if(s == 0)
			return -1;
		else
			if(s[0] == 0)
				return -1;
		ssize = strlen(s);
		for(i = start; i < size() - ssize; i++){
			if(charAt(i) == s[0]){
				for(j = 0; j < ssize; j++){
					if(charAt(i + j) != s[j])
						continue;
				}
				return i;
			}
		}
		return -1;
	}
	
	const int String::index(const char c, int start){
		unsigned int i;
		if(size() == 0)
			return -1;
		for(i = start; i < size(); i++){
			if(charAt(i) == c)
				return i;
		}
		return -1;
	}
	
	const int String::rindex(const String &s, int end){
		int e;
		unsigned int i, j;
		if(size() == 0)
			return -1;
		if(((String *)&s) == 0)
			return -1;
		else
			if(((String *)&s)->charAt(0) == 0)
				return -1;
		if(end == 0)
			e = size() - 1;
		else
			if((unsigned int)end > (size() - ((String *)&s)->size()))
				return -1;
			else
				e = end;
		for(i = e; i >= 0; i--){
			if(charAt(i) == ((String *)&s)->charAt(0)){
				for(j = 0; j < ((String *)&s)->size(); j++){
					if(charAt(i + j) != ((String *)&s)->charAt(j))
						continue;
				}
				return i;
			}
		}
	}
	
	const int String::rindex(const char *s, int end){
		unsigned int i, j, ssize, e;
		if(size() == 0)
			return -1;
		if(s == 0)
			return -1;
		else
			if(s[0] == 0)
				return -1;
		ssize = strlen(s);
		if(end == 0)
			e = size() - 1;
		else
			if((unsigned int)end > (size() - ssize))
				return -1;
			else
				e = end;
		for(i = e; i >= 0; i--){
			if(charAt(i) == s[0]){
				for(j = 0; j < ssize; j++){
					if(charAt(i + j) != s[j])
						continue;
				}
				return i;
			}
		}
		return -1;
	}
	
	const int String::rindex(const char c, int end){
		unsigned int i;
		if(size() == 0)
			return -1;
		if(end == 0)
			end = len - 1;
		for(i = end; i >= 0; i--){
			if(charAt(i) == c)
				return i;
		}
		return -1;
	}
	
	bool String::startsWith(String &s){
		unsigned int i;
		if(size() == 0)
			return false;
		if(s.size() > size())
			return false;
		for(i = 0; i < s.size(); i++){
			if(charAt(i) != s[i])
				return false;
		}
		return true;
	}
	
	bool String::startsWith(const char *s){
		unsigned int i;
		unsigned ssize;
		if(s == 0)
			return true;
		else
			if(s[0] == 0)
				return false;
		if(size() == 0)
			return false;
		ssize = strlen(s);
		if(ssize > size())
			return false;
		for(i = 0; i < ssize; i++){
			if(charAt(i) != s[i])
				return false;
		}
		return true;
	}
	
	bool String::startsIWith(const char *s){
		unsigned int i;
		unsigned ssize;
		if(s == 0)
			return true;
		else
			if(s[0] == 0)
				return false;
		if(size() == 0)
			return false;
		ssize = strlen(s);
		if(ssize > size())
			return false;
		for(i = 0; i < ssize; i++){
			if(tolower(charAt(i)) != tolower(s[i]))
				return false;
		}
		return true;
	}
	
	bool String::endsWith(String &s){
		unsigned int i, j;
		if(size() == 0)
			return false;
		if(s.size() > size())
			return false;
		for(i = s.size() - 1, j = size() - 1; (int)i >= 0; i--, j--){
			if(charAt(j) != s[i])
				return false;
		}
		return true;
	}
	
	bool String::endsWith(const char *s){
		unsigned int i, j;
		unsigned ssize;
		if(s == 0)
			return true;
		else
			if(s[0] == 0)
				return false;
		if(size() == 0)
			return false;
		ssize = strlen(s);
		if(ssize > size())
			return false;
		for(i = ssize - 1, j = size() - 1; (int)i >= 0; i--, j--){
			if(charAt(j) != s[i])
				return false;
		}
		return true;
	}
	
	String &String::deleteCharAt(const int pos){
		char *tmp;
		int i, j;
		if(size() == 0)
			return *this;
		tmp = new char[size() + 1];
		for(i = 0, j = 0; i < (int)size(); i++){
			if(i != pos)
				tmp[j++] = charAt(i);
		}
		tmp[j] = '\0';
		len--;
		xvr2_delete_array(buffer);
		buffer = tmp;
		return *this;
	}
	
	String &String::insertCharAt(const int pos, const char c){
		char *tmp;
		int i, j;
		if(size() == 0)
			return *this;
		tmp = new char[size() + 2];
		for(i = 0, j = 0; i < (int)size(); i++){
			if(i == pos)
				tmp[j++] = c;
			tmp[j++] = charAt(i);
		}
		tmp[j] = '\0';
		len++;
		xvr2_delete_array(buffer);
		buffer = tmp;
		return *this;
	}

	char *String::getSubstr(unsigned int start, unsigned int end){
		char *nbuf = 0;
		unsigned int i, j;
		unsigned int siz;
		if(end < start){
			throw Exception::InvalidParameter();
			return 0;
		}
		if(end >= size()){
			throw Exception::ArrayIndexOutOfLimits();
			return 0;
		}
		if(end == start)
			return 0;
		siz = (end - start) + 1;
		nbuf = (char *)Memory::allocBuffer(siz);
		Memory::clearBuffer((void *)nbuf, siz);
		for(i = start, j = 0; i < end; i++, j++){
			nbuf[j] = buffer[i];
		}
		return nbuf;
	}

};
