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
#include<stdlib.h>
//#include<stdio.h>
#include<ctype.h>
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

#if defined(__linux) || defined(__LINUX) || defined(__linux__) || defined(__LINUX__) || defined(__unix) || defined(__unix__)
	const String NL("\n");
#else
	const String NL("\r\n");
#endif

	template<typename _numericT>
	void num2char(_numericT num, std::string *str){
		std::stringstream ss;
		ss << num;
		str->assign(ss.str());
	}
	template<typename _numericT>
	_numericT char2num(const std::string *str){
		using std::ios_base;
		_numericT num;
		std::istringstream ss(str->c_str());
		ss >> num;
		if(ss.fail() || ss.bad())
			throw NumberException();
		return num;
	}
	
	
	/////////////////////////////// CONSTRUCTOR /////////////////////////
	String::String(){
	}
	
	String::String(const String &s){
		BasicString<char>::assign(s.c_str());
	}
	
	String::String(const char *s){
		BasicString<char>::assign(s);
	}
	
	String::String(const Int32 n){
		assign(n);
	}
	String::String(const UInt32 n){
		assign(n);
	}

	String::String(const Int64 n){
		assign(n);
	}
	String::String(const UInt64 n){
		assign(n);
	}
	
	String::String(const float n){
		assign(n);
	}
	
	String::String(const double n){
		assign(n);
	}
	
	String::String(const long double n){		assign(n);
	}
	String::String(const std::string &s){
		std::string::assign(s);
	}
	String::String(const std::string *s){

		std::string::assign(s->c_str());
	}
	
	String::String(const xvr2::Object &o){
		std::string::assign(((Object *)&o)->toString());
	}
	
	/////////////////////////////// ::assign() /////////////////////////
	String &String::assign(const char *s){
		BasicString<char>::assign(s);
		return *this;
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
		std::transform(
				std::string::begin(), 
				std::string::end(), 
				std::string::begin(), 
				(int(*)(int)) toupper
			);
		return *this;
	}
	
	const String& String::toLowerCase(){
		std::transform(
				std::string::begin(), 
				std::string::end(), 
				std::string::begin(), 
				(int(*)(int)) tolower
			);
		return *this;
	}
	
	//////////////////////////////////////////// STRING TO NUMERIC CONVERSIONS ///////////////////////////////////////
	const int String::toInt(){
		return char2num<int>(this);
	}
	
	const unsigned int String::toUInt(){
		return char2num<unsigned int>(this);
	}
	
	const float String::toFloat(){
		return char2num<float>(this);
	}
	
	const double String::toDouble(){
		return char2num<double>(this);
	}
	
	const long double String::toLongDouble(){
		return char2num<long double>(this);
	}
	
	const Int64 String::toInt64(){
		return char2num<Int64>(this);
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
	int String::compare(const String &s) const{
		return BasicString<char>::compare(s.c_str());
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
		if(s == 0)
			return true;
		else
			if(s[0] == 0)
				return false;
		if(size() == 0)
			return false;
		UInt32 ssize = strlen(s);
		if(ssize > size())
			return false;
		for(UInt32 i = 0; i < ssize; i++){
			if(tolower(charAt(i)) != tolower(s[i]))
				return false;
		}
		return true;
	}

	std::string String::toString(){
		return std::string(c_str());
	}

	String String::getSubstr(int start, int end){
		return BasicString<char>::substr(start, end);
	}

	void String::eat(const char *data, int len){
		BasicString<char>::append(data, len);
	}
	
	String &String::trimLeft(const char c){
		while(size() > 0 &&	at(0) == c){
			erase(begin(), begin() + 1);
		}
		return *this;
	}
	
	String &String::trimRight(const char c){
		while(size() > 0 && at(size() - 1) == c){
			erase(end() - 1, end());
		}
		return *this;
	}
}
