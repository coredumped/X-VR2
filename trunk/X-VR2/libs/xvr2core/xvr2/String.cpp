/*
 $Id$
 */
#include"config.h"
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include "_xvr2ClassNames.h"
#include "String.h"
#include "ArrayIndexOutOfLimitsException.h"
#include "NumberException.h"
#include "NullPointerException.h"
#include<ctype.h>
#if __GNUC__ < 3
#include<iostream.h>
#include<string.h>
#else
#include<iostream>
#include<string>
#include<sstream>
#endif
#include<errno.h>
#include "Memory.h"
#ifdef HAVE_POW
#include<math.h>
#endif

namespace xvr2{

	template<typename _numericT>
	void num2char(_numericT num, std::string *str){
		std::stringstream ss;
		ss << num;

		str->assign(ss.str());
	}

	/*void int2char(int num, char buf[]){
		std::stringstream ss;
		//sprintf(buf, "%d", num);
		ss << num;
	}

	void long2char(long num, char buf[]){
		sprintf(buf, "%ld", num);
	}*/
	
	/*char *String::toCharPtr() const {
		if(this == 0x0)
			throw NullPointer();
		return buffer;
	}*/
	
	String::~String(){
		//destroy();
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
		debugmsg(this, " String::~String()\n");
	#endif
#endif
	}
	
	String::String(){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
	}
	
	String::String(const String &s){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		std::string::assign(s.c_str());
	}
	
	String::String(const char *s){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		std::string::assign(s);
	}
	
	String::String(const int n){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}

#ifndef __x86_64__
	String::String(const long n){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
#endif
	
	String::String(const unsigned int n){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const float n){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const double n){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const long double n){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const Int64 n){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String &String::assign(const char *s){
		std::string::assign(s);
	}
	
	String &String::assign(const int n){
		char num[14];
		//int2char(n, num);
		num2char<int>(n, this);
		//std::string::assign(num);
		return *this;
	}

#ifndef __x86_64__
	String &String::assign(const long n){
		char num[24];
		//long2char(n, num);
		num2char<int>(n, this);
		//std::string::assign(num);
		return *this;
	}
#endif
	
	String &String::assign(const unsigned int n){
		//char num[14];
		num2char<unsigned int>(n, this);
		/*sprintf(num, "%u", n);
		std::string::assign(num);*/
		return *this;
	}
	
	String &String::assign(const float n){
		num2char<float>(n, this);
		/*char num[80];
		sprintf(num, "%f", n);
		std::string::assign(num);*/
		return *this;
	}
	
	String &String::assign(const double n){
		num2char<double>(n, this);
		/*char num[80];
		sprintf(num, "%f", n);
		std::string::assign(num);*/
		return *this;
	}
	
	String &String::assign(const long double n){
		num2char<long double>(n, this);
		/*char num[256];
		sprintf(num, "%Lf", n);
		assign(num);
		std::string::assign(num);*/
		return *this;
	}
	
	String &String::assign(const Int64 n){
		num2char<Int64>(n, this);
		/*char num[32];
		sprintf(num, "%lld", n);
		assign(num);
		std::string::assign(num);*/
		return *this;
	}

	String &String::assign(const String &sstr){
		std::string::assign(sstr.c_str());
		return *this;
	}

	/*const String &String::assign(const char *s){
		CharString::assign(s);
		return *this;
	}*/

	String &String::assign(const char c){
		std::string::assign(1, c);
		return *this;
	}
	
	String &String::concat(const String &s){
		//CharString::concat(s.buffer);
		std::string::append(s);
		return *this;
	}
	String &String::concat(const char c){
		//CharString::concat(c);
		std::string::append(1, c);
		return *this;
	}
	String &String::concat(const char *s){
		//CharString::concat(s);
		std::string::append(s);
		return *this;
	}
	String &String::concat(const int n){
		/*char *buf;
		buf = new char[14];
		int2char(n, buf);
		concat(buf);
		delete[] buf;
		buf = 0;*/
		std::string buf;
		num2char<int>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const unsigned int n){
		/*char *buf;
		buf = new char[14];
		sprintf(buf, "%u", n);
		concat(buf);
		delete[] buf;
		buf = 0;*/
		std::string buf;
		num2char<unsigned int>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const float n){
		/*char *buf;
		buf = new char[256];
		sprintf(buf, "%f", n);
		concat((const char *)buf);
		delete[] buf;
		buf = 0;*/
		std::string buf;
		num2char<float>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const double n){
		/*char *buf;
		buf = new char[256];
		sprintf(buf, "%f", n);
		concat(buf);
		delete[] buf;
		buf = 0;*/
		std::string buf;
		num2char<double>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const long double n){
		/*char *buf;
		buf = new char[256];
		sprintf(buf, "%Lf", n);
		concat(buf);
		delete[] buf;
		buf = 0;*/
		std::string buf;
		num2char<long double>(n, &buf);
		concat(buf);	
		return *this;
	}
	
	String &String::concat(const Int64 n){
		/*char *buf;
		buf = new char[25];
		sprintf(buf, "%lld", n);
		concat(buf);
		delete[] buf;
		buf = 0;*/
		std::string buf;
		num2char<Int64>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const UInt64 n){
		/*char *buf;
		buf = new char[25];
		sprintf(buf, "%llu", n);
		concat(buf);
		delete[] buf;
		buf = 0;*/
		std::string buf;
		num2char<UInt64>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String& String::operator=(const int n){
		assign(n);
		return *this;
	}

#ifndef __x86_64__
	String& String::operator=(const long n){
		assign(n);
		return *this;
	}
#endif
	
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

	String& String::operator=(const String &s){
		std::string::assign(s.c_str());
		return *this;
	}
	
	const String& String::operator+=(const String &s){
		concat(s);
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
		stream << s.c_str();
		return stream;
	}
	
	char String::charAt(int i) const{
		if(i < 0 || i >= size())
			throw ArrayIndexOutOfLimits();
		return at(i);
	}
	
	char String::operator[](int i) const {
		return charAt(i);
	}
	
	/*const String &String::trimLeft(const char c){
		int i = 0;
#ifndef HAVE_STRCPY
		int j = 0;
#endif
		char *buf, *ptr;
		if(size() == 0){
			return *this;
		}
		buf = new char[size() + 1];
		ptr = (char *)data();
		while(*(ptr++) == c) 
			i++;
#ifdef HAVE_STRCPY
		strcpy(buf, ptr);
#else
		for(j = 0; at(i) != 0; j++, i++)
			buf[j] = at(i);
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
		if(size() == 0){
			return *this;
		}
		for(i = size() - 1; i >=0 && at(i) == c; i--){
			at(i) = 0;
		}
		return *this;
	}*/
	
	String& String::trim(const char c){
		trimLeft(c);
		trimRight(c);
		return *this;
	}
	
	const String& String::toUpperCase(){
		register int i;
		std::stringstream ss;
		for(i = 0; i < size(); i++){
			//buffer[i] = toupper(buffer[i]);
			ss << (char)toupper(at(i));
		}
		assign(ss.str().c_str());
		return *this;
	}
	
	const String& String::toLowerCase(){
		register int i;
		std::stringstream ss;
		for(i = 0; i < size(); i++){
			//buffer[i] = tolower(buffer[i]);
			ss << (char)tolower(at(i));
		}
		assign(ss.str().c_str());
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
		if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
#ifdef HAVE_STRTOL
		num = strtol(c_str(), 0, 10);
		return num;
#else
		return atoi(c_str());
#endif
	}
	
	const unsigned int String::toUInt(){
		unsigned int num = 0, low = 0;
		unsigned int i, j;
		char first_char = at(0);
		if(size() == 0)
			return 0;
		if(first_char == 0)
			return 0;
		if(first_char == '+')
			low = 1;
		if(isdigit(first_char) || first_char == '+'){
			for(i = (size() - 1), j = 0; i >= low; i--, j++){
				if(!isdigit(at(i))){
					throw NumberException();
				}
				num = num + (at(i) - '0')* __power(j);
			}
		}
		else
			if(first_char != '+'){
				throw NumberException();
			}
		return num;
	}
	
	const float String::toFloat(){
		if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return (float)toDouble();
	}
	
	const double String::toDouble(){
		if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return atof(c_str());
	}
	
	const long double String::toLongDouble(){
		if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return strtold(c_str(), 0);
	}
	
	const Int64 String::toInt64(){
		if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return atoll(c_str());
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
		return equals(s.c_str());
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
		return (size() == 1 && at(0) == c)?true:false;
	}
	bool String::equals(const char *s) const{
		return (compare(s) == 0)?true:false;
	}
	bool String::equals(const String &s) const{
		return (compare(c_str()) == 0)?true:false;
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
		/*int i;
		//Use this algorithm to favor no allocation of addional 
		//memory
		if(size() == 0)
			return *this;
		else{
			if(at(0) == 0)
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
		buffer[i - 1] = 0;*/
		std::string::erase(0);
		return *this;
	}
	
	const String &String::deleteLast(){
		/*if(buffer == 0)
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
		buffer[size() - 1] = '\0';*/
		std::string::erase(size() - 1);
		return *this;
	}
	
	bool String::endsWith(const String &s) const{
		return (std::string::rfind(s.toCharPtr()) == 0)?true:false;
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
		/*char *tmp;
		int i, j;
		if(size() == 0)
			return;
		tmp = new char[size() + 1];
		for(i = 0, j = 0; i < (int)size(); i++){
			if(i != pos)
				tmp[j++] = charAt(i);
		}
		tmp[j] = '\0';
		assign(tmp);
		delete[] tmp;
		return;*/
		erase(pos);
	}
	
	void String::insertCharAt(const int pos, const char c) {
		/*char *tmp;
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
		//xvr2_delete_array(buffer);
		delete[] buffer;
		buffer = tmp;
		return;*/
		std::string::insert(pos, 1, c);
	}

	char *String::getSubstr(int start, int end){
		char *nbuf = 0;
		int i, j;
		int siz;
		if(end < start){
			throw InvalidParameter();
			return 0;
		}
		if(end >= size()){
			throw ArrayIndexOutOfLimits();
			return 0;
		}
		if(end == start)
			return 0;
		siz = (end - start) + 1;
		nbuf = (char *)Memory::allocBuffer(siz);
		Memory::clearBuffer((void *)nbuf, siz);
		for(i = start, j = 0; i < end; i++, j++){
			nbuf[j] = at(i);
		}
		return nbuf;
	}

	const std::string &String::toString(){
		if(string_representation == 0){
			string_representation = new std::string(toCharPtr());
		}
		return *string_representation;
	}

	String::String(const std::string &s){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		std::string::assign(s);
	}
	String::String(const std::string *s){
#if __GNUC__ < 3
		Object::setClassName(xvr2::_xvr2String);
#endif
		std::string::assign(s->c_str());
	}

	/*const String &String::assign(const std::string &sstr){
		CharString::assign(sstr.c_str());
		return *this;
	}*/

	String &String::assign(const std::string *sstr){
		std::string::assign(sstr->c_str());
		return *this;
	}
};
