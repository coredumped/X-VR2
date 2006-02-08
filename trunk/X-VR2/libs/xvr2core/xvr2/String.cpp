/*
 $Id$
 */
#include"config.h"
#include<stdlib.h>
//#include<stdio.h>
#include<ctype.h>
#include "_xvr2ClassNames.h"
#include "String.h"
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
#ifndef HAVE_STRTOUL
#ifdef HAVE_POW
#include<math.h>
#else
#error Unable to make numeric conversions
#endif
#endif

namespace xvr2{

	template<typename _numericT>
	void num2char(_numericT num, std::string *str){
		std::stringstream ss;
		ss << num;
		str->assign(ss.str());
	}
	template<typename _numericT>
	_numericT char2num(const std::string *str){
		_numericT num;
		std::istringstream ss(str->c_str());
		ss >> num;
		return num;
	}
	////////////////////////////// DESTRUCTOR ///////////////////////////
	String::~String(){
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
		debugmsg(this, " String::~String()\n");
	#endif
#endif
	}
	
	/////////////////////////////// CONSTRUCTOR /////////////////////////
	String::String(){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
	}
	
	String::String(const String &s){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		BasicString<char>::assign(s.c_str());
	}
	
	String::String(const char *s){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		BasicString<char>::assign(s);
	}
	
	String::String(const Int32 n){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	String::String(const UInt32 n){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}

	String::String(const Int64 n){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	String::String(const UInt64 n){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const float n){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const double n){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	
	String::String(const long double n){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		assign(n);
	}
	String::String(const std::string &s){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		std::string::assign(s);
	}
	String::String(const std::string *s){
#ifdef USE_EMBEDDED_CLASSNAMES
		Object::setClassName(xvr2::_xvr2String);
#endif
		std::string::assign(s->c_str());
	}
	
	/////////////////////////////// ::assign() /////////////////////////
	String &String::assign(const char *s){
		BasicString<char>::assign(s);
	}
	
	String &String::assign(const Int32 n){
		num2char<int>(n, this);
		return *this;
	}
	String &String::assign(const Int64 n){
		num2char<Int64>(n, this);
		return *this;
	}
	String &String::assign(const UInt32 n){
		num2char<int>(n, this);
		return *this;
	}
	String &String::assign(const UInt64 n){
		num2char<Int64>(n, this);
		return *this;
	}
	
	String &String::assign(const float n){
		num2char<float>(n, this);
		return *this;
	}
	
	String &String::assign(const double n){
		num2char<double>(n, this);
		return *this;
	}
	
	String &String::assign(const long double n){
		num2char<long double>(n, this);
		return *this;
	}

	String &String::assign(const String &sstr){
		BasicString<char>::assign(sstr.c_str());
		return *this;
	}

	String &String::assign(const char c){
		BasicString<char>::assign(1, c);
		return *this;
	}

	String &String::assign(const std::string *sstr){
		std::string::assign(sstr->c_str());
		return *this;
	}
	
	/////////////////////////////// ::concat() /////////////////////////
	String &String::concat(const String &s){
		BasicString<char>::append(s);
		return *this;
	}
	String &String::concat(const char c){
		BasicString<char>::append(1, c);
		return *this;
	}
	String &String::concat(const char *s){
		BasicString<char>::append(s);
		return *this;
	}
	String &String::concat(const Int32 n){
		std::string buf;
		num2char<Int32>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const UInt32 n){
		std::string buf;
		num2char<UInt32>(n, &buf);
		concat(buf);
		return *this;
	}
	String &String::concat(const Int64 n){
		std::string buf;
		num2char<Int64>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const UInt64 n){
		std::string buf;
		num2char<UInt64>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const float n){
		String buf(n);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const double n){
		std::string buf;
		num2char<double>(n, &buf);
		concat(buf);
		return *this;
	}
	
	String &String::concat(const long double n){
		std::string buf;
		num2char<long double>(n, &buf);
		concat(buf);	
		return *this;
	}
	
	/////////////////////////////// ::operator=() /////////////////////////
	String& String::operator=(const Int32 n){
		assign(n);
		return *this;
	}
	String& String::operator=(const UInt32 n){
		assign(n);
		return *this;
	}
	String& String::operator=(const Int64 n){
		assign(n);
		return *this;
	}
	String& String::operator=(const UInt64 n){
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

	String& String::operator=(const String &s){
		std::string::assign(s.c_str());
		return *this;
	}
	
	/////////////////////////////// ::operator+=() /////////////////////////
	const String& String::operator+=(const String &s){
		concat(s);
		return *this;
	}

	const String& String::operator+=(const Int32 n){
		concat(n);
		return *this;
	}
	const String& String::operator+=(const UInt32 n){
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
	
	std::ostream& operator<<(std::ostream& stream, const String &s){
		stream << s.c_str();
		return stream;
	}
	
	const String& String::toUpperCase(){
		std::transform(std::string::begin(), std::string::end(), std::string::begin(), (int(*)(int)) toupper);
		return *this;
	}
	
	const String& String::toLowerCase(){
		std::transform(std::string::begin(), std::string::end(), std::string::begin(), (int(*)(int)) tolower);
		return *this;
	}
	
	//////////////////////////////////////////// STRING TO NUMERIC CONVERSIONS ///////////////////////////////////////
	const int String::toInt(){
		return char2num<int>(this);
		/*
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
#endif*/
	}
	
	const unsigned int String::toUInt(){
		return char2num<unsigned int>(this);
		/*unsigned int num = 0, low = 0;
		unsigned int i, j;
		char first_char = at(0);
		if(size() == 0)
			return 0;
		if(first_char == 0)
			return 0;
#ifdef HAVE_STRTOUL
		num = strtoul(c_str(), 0, 10);
#else
		if(first_char == '+')
			low = 1;
		if(isdigit(first_char) || first_char == '+'){
			for(i = (size() - 1), j = 0; i >= low; i--, j++){
				if(!isdigit(at(i))){
					throw NumberException();
				}
				num = num + (at(i) - '0')* pow(10.0, (double)j);
			}
		}
		else
			if(first_char != '+'){
				throw NumberException();
			}
#endif
		return num;*/
	}
	
	const float String::toFloat(){
		return char2num<float>(this);
		/*if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return (float)toDouble();*/
	}
	
	const double String::toDouble(){
		return char2num<double>(this);
		/*if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return atof(c_str());*/
	}
	
	const long double String::toLongDouble(){
		return char2num<long double>(this);
		/*if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return strtold(c_str(), 0);*/
	}
	
	const Int64 String::toInt64(){
		return char2num<Int64>(this);
		/*if(size() == 0)
			return 0;
		if(at(0) == 0)
			return 0;
		return atoll(c_str());*/
	}
	
	/////////////////////////////// ::operator==() /////////////////////////
	const bool String::operator==(const Int32 n){
		return equals(n);
	}
	const bool String::operator==(const UInt32 n){
		return equals(n);
	}
	const bool String::operator==(const Int64 n){
		return equals(n);
	}
	const bool String::operator==(const UInt64 n){
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
	
	/////////////////////////////// ::operator!=() /////////////////////////
	const bool String::operator!=(const Int32 n){
		return equals(n)?false:true;
	}
	const bool String::operator!=(const UInt32 n){
		return equals(n)?false:true;
	}
	const bool String::operator!=(const Int64 n){
		return equals(n)?false:true;
	}
	const bool String::operator!=(const UInt64 n){
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
	
	/////////////////////////////// ::equals() /////////////////////////
	bool String::equals(const char c) const{
		return (size() == 1 && at(0) == c)?true:false;
	}

	bool String::equals(const String &s){
		return (compare(s.c_str()) == 0)?true:false;
	}
	bool String::equals(const String &s) const{
		return (compare(s.c_str()) == 0)?true:false;
	}
	const bool String::equals(const Int32 n){
		String s(n);
		return (compare(s.c_str()) == 0)?true:false;
	}
	const bool String::equals(const UInt32 n){
		String s(n);
		return (compare(s.c_str()) == 0)?true:false;
	}
	const bool String::equals(const Int64 n){
		String s(n);
		return (compare(s.c_str()) == 0)?true:false;
	}
	const bool String::equals(const UInt64 n){
		String s(n);
		return (compare(s.c_str()) == 0)?true:false;
	}
	const bool String::equals(const float n){
		String s(n);
		return (compare(s.c_str()) == 0)?true:false;
	}
	const bool String::equals(const double n){
		String s(n);
		return (compare(s.c_str()) == 0)?true:false;
	}
	const bool String::equals(const long double n){
		String s(n);
		return (compare(s.c_str()) == 0)?true:false;
	}
	
	/////////////////////////////// ::endsWith() /////////////////////////
	bool String::endsWith(const String &s) const{
		return BasicString<char>::endsWith(s.c_str());
	}

	bool String::endsIWith(const char *s) const{
		return BasicString<char>::endsWith(s);
	}

	/////////////////////////////// ::statrsWith() /////////////////////////
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

	std::string String::toString(){
		/*if(string_representation == 0){
			string_representation = new std::string(toCharPtr());
		}
		return *string_representation;*/
		return std::string(c_str());
	}

	String String::getSubstr(int start, int end){
		return BasicString<char>::substr(start, end);
	}
};
