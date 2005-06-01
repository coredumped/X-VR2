/*
 $Id$
 */
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<xvr2/_xvr2ClassNames.h>
#include<xvr2/String.h>
#include<xvr2/ArrayIndexOutOfLimitsException.h>
#include<xvr2/NumberException.h>
#include<xvr2/NullPointerException.h>
#include<ctype.h>
#ifdef USING_GCC3
#include<iostream>
#include<string>
#else
#include<iostream.h>
#include<string.h>
#endif
#include<errno.h>
#include<xvr2/Memory.h>
#ifdef HAVE_POW
#include<math.h>
#endif

namespace xvr2{

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
	
	/*char *String::toCharPtr() const {
		if(this == 0x0)
			throw Exception::NullPointer();
		return buffer;
	}*/
	
	String::~String(){
		destroy();
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
		debugmsg(this, " String::~String()\n");
	#endif
#endif
	}
	
	String::String():CharString(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
	}
	
	String::String(const String &s):CharString(s.buffer){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
	}
	
	String::String(const char *s):CharString(s){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
	}
	
	String::String(const int n):CharString(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const unsigned int n):CharString(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const float n):CharString(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const double n):CharString(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const long double n):CharString(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const Int64 n):CharString(){
#ifndef USING_GCC3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	/*void String::assign(const char *s){
		::assign(s);
	}*/
	
	const String &String::assign(const int n){
		char num[14];
		int2char(n, num);
		assign(num);
		return *this;
	}
	
	const String &String::assign(const unsigned int n){
		char num[14];
		/*char *num = 0;
		num = new char[13];*/
		sprintf(num, "%u", n);
		assign(num);
		//xvr2_delete_array(num);
		return *this;
	}
	
	const String &String::assign(const float n){
		char num[80];
		/*char *num = 0;
		num = new char[80];*/
		sprintf(num, "%f", n);
		assign(num);
		//xvr2_delete_array(num);
		return *this;
	}
	
	const String &String::assign(const double n){
		char num[80];
		/*char *num = 0;
		num = new char[80];*/
		sprintf(num, "%f", n);
		assign(num);
		//xvr2_delete_array(num);
		return *this;
	}
	
	const String &String::assign(const long double n){
		char num[256];
		/*char *num = 0;
		num = new char[256];*/
		sprintf(num, "%Lf", n);
		assign(num);
		//xvr2_delete_array(num);
		return *this;
	}
	
	const String &String::assign(const Int64 n){
		char num[32];
		/*char *num = 0;
		num = new char[32];*/
		sprintf(num, "%lld", n);
		assign(num);
		//xvr2_delete_array(num);
		return *this;
	}

	const String &String::assign(const String &sstr){
		CharString::assign(sstr);
		return *this;
	}

	const String &String::assign(const char *s){
		CharString::assign(s);
		return *this;
	}

	/*const String &String::assign(const char c){
		CharString::assign(c);
		return *this;
	}*/
	
	const String &String::concat(const String &s){
		CharString::concat(s.buffer);
		return *this;
	}
	const String &String::concat(const char c){
		CharString::concat(c);
		return *this;
	}
	const String &String::concat(const char *s){
		CharString::concat(s);
		return *this;
	}
	const String &String::concat(const int n){
		char *buf;
		buf = new char[14];
		int2char(n, buf);
		concat(buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	const String &String::concat(const unsigned int n){
		char *buf;
		buf = new char[14];
		sprintf(buf, "%u", n);
		concat(buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	const String &String::concat(const float n){
		char *buf;
		buf = new char[256];
		sprintf(buf, "%f", n);
		concat((const char *)buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	const String &String::concat(const double n){
		char *buf;
		buf = new char[256];
		sprintf(buf, "%f", n);
		concat(buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	const String &String::concat(const long double n){
		char *buf;
		buf = new char[256];
		sprintf(buf, "%Lf", n);
		concat(buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	const String &String::concat(const Int64 n){
		char *buf;
		buf = new char[25];
		sprintf(buf, "%lld", n);
		concat(buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	const String &String::concat(const UInt64 n){
		char *buf;
		buf = new char[25];
		sprintf(buf, "%llu", n);
		concat(buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	const String& String::operator=(const int n){
		assign(n);
		return *this;
	}
	
	const String& String::operator=(const unsigned int n){
		assign(n);
		return *this;
	}
	
	const String& String::operator=(const float n){
			assign(n);
		return *this;
	}
	
	const String& String::operator=(const double n){
		assign(n);
		return *this;
	}
	
	const String& String::operator=(const long double n){
		assign(n);
		return *this;
	}
	
	const String& String::operator=(const Int64 n){
		assign(n);
		return *this;
	}

	const String& String::operator=(const String &s){
		assign(s);
		return *this;
	}
	
	const String& String::operator+=(const String &s){
		concat(s.buffer);
		return *this;
	}

	const String& String::operator+=(const int n){
		concat(n);
		return *this;
	}
	
	const String& String::operator+=(const unsigned int n){
		concat(n);
		return *this;
	}
	
	const String& String::operator+=(const float n){
		concat(n);
		return *this;
	}
	
	const String& String::operator+=(const double n){
		concat(n);
		return *this;
	}
	
	const String& String::operator+=(const long double n){
		concat(n);
		return *this;
	}
	
	const String& String::operator+=(const Int64 n){
		concat(n);
		return *this;
	}
	
	const String& String::operator+=(const UInt64 n){
		concat(n);
		return *this;
	}
	
	std::ostream& operator<<(std::ostream& stream, const String &s){
		stream << s.buffer;
		return stream;
	}
	
	char String::charAt(int i) const{
		if(i < 0 || i >= len)
			throw Exception::ArrayIndexOutOfLimits();
		return buffer[i];
	}
	
	char String::operator[](int i) const {
		return charAt(i);
	}
	
	const String &String::trimLeft(const char c){
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
		//xvr2_delete_array(buf);
		delete[] buf;
		buf = 0;
		return *this;
	}
	
	
	const String &String::trimRight(const char c){
		int i;
		if(buffer == 0){
			throw Exception::NullPointer();
			return *this;
		}
		for(i = len - 1; i >=0 && buffer[i] == c; i--){
			buffer[i] = 0;
			len--;
		}
		return *this;
	}
	
	const String& String::trim(const char c){
		trimLeft(c);
		trimRight(c);
		return *this;
	}
	
	const String& String::toUpperCase(){
		register int i;
		for(i = 0; i < len; i++){
			buffer[i] = toupper(buffer[i]);
		}
		return *this;
	}
	
	const String& String::toLowerCase(){
		register int i;
		for(i = 0; i < len; i++){
			buffer[i] = tolower(buffer[i]);
		}
		return *this;
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
	
	const bool String::operator==(const int n){
		return equals(n);
	}
	const bool String::operator==(const unsigned int n){
		return equals(n);
	}
	
	const bool String::operator==(const float n){
		return equals(n);
	}
	
	const bool String::operator==(const double n){
		return equals(n);
	}
	
	const bool String::operator==(const long double n){
		return equals(n);
	}
	
	const bool String::operator==(const Int64 n){
		return equals(n);
	}

	bool String::operator==(const String &s) const{
		return equals(s.buffer);
	}
	
	const bool String::operator!=(const int n){
		return equals(n)?false:true;
	}
	const bool String::operator!=(const unsigned int n){
		return equals(n)?false:true;
	}
	
	const bool String::operator!=(const float n){
		return equals(n)?false:true;
	}
	
	const bool String::operator!=(const double n){
		return equals(n)?false:true;
	}
	
	const bool String::operator!=(const long double n){
		return equals(n)?false:true;
	}
	
	const bool String::operator!=(const Int64 n){
		return equals(n)?false:true;
	}
	
	bool String::equals(const char c) const{
		return (len == 1 && buffer[0] == c)?true:false;
	}
	bool String::equals(const char *s) const{
		return (compare(s) == 0)?true:false;
	}
	bool String::equals(const String &s) const{
		return (compare(s.buffer) == 0)?true:false;
	}
	const bool String::equals(const int n){
		String s(n);
		return equals(s);
	}
	
	const bool String::equals(const unsigned int n){
		String s(n);
		return equals(s);
	}
	
	const bool String::equals(const float n){
		String s(n);
		return equals(s);
	}
	
	const bool String::equals(const double n){
		String s(n);
		return equals(s);
	}
	
	const bool String::equals(const long double n){
		String s(n);
		return equals(s);
	}
	
	const bool String::equals(const Int64 n){
		String s(n);
		return equals(s);
	}
	
	const String &String::deleteFirst(){
		int i;
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
	
	const String &String::deleteLast(){
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
	
	bool String::startsWith(const String &s) const{
		return (index(s.toCharPtr()) == 0)?true:false;
	}

	bool String::startsIWith(const char *s) const{
		int i;
		int ssize;
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
	
	void String::deleteCharAt(const int pos) {
		char *tmp;
		int i, j;
		if(size() == 0)
			return;
		tmp = new char[size() + 1];
		for(i = 0, j = 0; i < (int)size(); i++){
			if(i != pos)
				tmp[j++] = charAt(i);
		}
		tmp[j] = '\0';
		len--;
		//xvr2_delete_array(buffer);
		delete[] buffer;
		buffer = tmp;
		return;
	}
	
	void String::insertCharAt(const int pos, const char c) {
		char *tmp;
		int i, j;
		if(size() == 0)
			return;
		tmp = new char[size() + 2];
		for(i = 0, j = 0; i < (int)size(); i++){
			if(i == pos)
				tmp[j++] = c;
			tmp[j++] = charAt(i);
		}
		tmp[j] = '\0';
		len++;
		//xvr2_delete_array(buffer);
		delete[] buffer;
		buffer = tmp;
		return;
	}

	char *String::getSubstr(int start, int end){
		char *nbuf = 0;
		int i, j;
		int siz;
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
