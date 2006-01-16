/*
 $Id$
 */
#ifndef __XVR2_STRING_H__
#define __XVR2_STRING_H__
#define __XVR2_ENABLE_BASIC_STRING__
#include<xvr2/BasicString.h>
#include<xvr2/StringException.h>
#include<xvr2/InvalidParameterException.h>
#include<xvr2/BufferTooSmall.h>
#include<iostream>

namespace xvr2{
/**
 * This a string treatment class, it has a lot of methods and the
 * main idea is eliminate de use of the common tricks we use everyday
 * while we work with strings.
 * Many times when we work with strings we leave BIG memory leaks
 * in our programs, the main idea here is to help the programmer
 * by providing here a very complete strig treatment tool for
 * everyday use.
 *
 * TODO
 * reimplement all conversions and use the fastest algorithms possible, if
 * you think that is possible to use standard C library conversion functions
 * and that his functions as portable across al platforms targeted, then use
 * them as needed.
 */
class String:public CharString{
	private:
		/** Eliminates the contents of buffer and sets len to zero */
		//void destroy();
	protected:
	public:
		/** Default constructor, it initializes buffer and len to zero */
		String();
		/** \fn String(String &s)
		 *  This constructor initializes an instance of this class
		 *  by taking a another reference of the same class as
		 *  parameter
		 *  \param s is the String to be copied */
		String(const String &s);
		/** This constructor initializes an instance of this class
		 *  by taking an array of chars */
		String(const char *s);
#ifndef __x86_64__
		/** This constructor initializes an instance of this class
		 *  by transforming an integer to an array of chars and
		 *  then calling assign(const char *s); */
		String(const long n);
#endif
		String(const int n);
		/** This constructor initializes an instance of this class
		 *  by transforming an unsigned integer to an array 
		 *  of chars and then calling assign(const char *s); */
		String(const unsigned int n);
		/** This constructor initializes an instance of this class
		 *  by transforming a float to an array of chars and
		 *  then calling assign(const char *s); */
		String(const float n);
		/** This constructor initializes an instance of this class
		 *  by transforming a double to an array of chars and
		 *  then calling assign(const char *s); */
		String(const double n);
		/** This constructor initializes an instance of this class
		 *  by transforming a long double to an array of chars and
		 *  then calling assign(const char *s); */
		String(const long double n);
		/** This constructor initializes an instance of this class
		 *  by transforming a Int64 to an array of chars and
		 *  then calling assign(const char *s); */
		String(const Int64 n);

		/**
		 * Compatibility constructors for the std::string class */
		String(const std::string &s);
		String(const std::string *s);
		/** Destructor, eliminates the contents of buffer and
		 *  sets len to zero by calling the method destroy(); */
		~String();
		/** Assigns the contents of <b>s</b> to buffer */
		//void assign(const char *s);
		/** Transforms and assigns <b>n</b> to the current String */
		const String &assign(const int n);
#ifndef __x86_64__
		const String &assign(const long n);
#endif
		/** Transforms and assigns <b>n</b> to the current String */
		const String &assign(const unsigned int n);
		/** Transforms and assigns <b>n</b> to the current String */
		const String &assign(const float n);
		/** Transforms and assigns <b>n</b> to the current String */
		const String &assign(const double n);
		/** Transforms and assigns <b>n</b> to the current String */
		const String &assign(const long double n);
		/** Transforms and assigns <b>n</b> to the current String */
		const String &assign(const Int64 n);
		/** replaces the contents of the string with sstr */
		const String &assign(const char *sstr);
		//const String &assign(const char c);
		const String &assign(const String &sstr);
		const String &assign(const std::string &s);
		const String &assign(const std::string *s);
		/** transforms and concatenates s to the current String */
		const String &concat(const char *s);
		const String &concat(const char c);
		/** transforms and concatenates s to the current String */
		const String &concat(const String &s);
		/** Transforms and concatenates n to the current String */
		const String &concat(const int n);
		/** transforms and concatenates n to the current String */
		const String &concat(const unsigned int n);
		/** transforms and concatenates n to the current String */
		const String &concat(const float n);
		/** transforms and concatenates n to the current String */
		const String &concat(const double n);
		/** transforms and concatenates n to the current String */
		const String &concat(const long double n);
		/** transforms and concatenates n to the current String */
		const String &concat(const Int64 n);
		/** transforms and concatenates n to the current String */
		const String &concat(const UInt64 n);
		/** Transforms n and assigns it to buffer by calling 
		 *  assign(const char *); */
#ifndef __x86_64__
		const String& operator=(const long n);
#endif
		const String& operator=(const int n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		const String& operator=(const unsigned int n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		const String& operator=(const float n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		const String& operator=(const double n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		const String& operator=(const long double n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		const String& operator=(const Int64 n);
		const String& operator=(const String &s);
		const String& operator+=(const String &s);
		/** Transforms <b>n</b> and concatenates it to the current String */
		const String& operator+=(const int n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		const String& operator+=(const unsigned int n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		const String& operator+=(const float n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		const String& operator+=(const double n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		const String& operator+=(const long double n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		const String& operator+=(const Int64 n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		const String& operator+=(const UInt64 n);
		/** The main idea behind this is take advantage of the
		 * << operator of the ostream class, this way, you can
		 * use this class with streams<br>
		 * <b>String a = "hello world";</b><br>
		 * you would normally do:<br>
		 * <b>cout << a.toCharPtr() << endl;</b><br>
		 * with this operator you can just:<br>
		 * <b>cout << a << endl;</b> */
		friend std::ostream& operator<<(std::ostream& stream, const String &s);
		/** Returns the character at position i */
		char charAt(int i) const;
		/** Returns the character at position i by overriding
		 * the operator[] */
		char operator[](int i) const ;
		/** Eliminates all ocurrences of the c character that
		 * appears at left of the string */
		const String& trimLeft(const char c = ' ');
		/** Eliminates all ocurrences of the c character that
		 * appears at right of the string */
		const String& trimRight(const char c = ' ');
		/** Eliminates all ocurrences of the c character that
		 * appears at the beginning and the end of the string */
		const String& trim(const char c = ' ');
		/** Transforms the string to uppercase letters only */
		const String& toUpperCase();
		/** Transforms the string to lowercase letters only */
		const String& toLowerCase();
		/** Transforms the contents of the string to an integer
		 * if the string can't be translated to a number then
		 * the exception NumberException is thrown */
		const int toInt();
		/** Transforms the contents of the string to an unsigned
		 * integer if the string can't be translated to a number
		 * then the exception NumberException is thrown */
		const unsigned int toUInt();
		/** Transforms the contents of the string to a float
		 * if the string can't be translated to a number then
		 * the exception NumberException is thrown */
		const float toFloat();
		/** Transforms the contents of the string to a double
		 * if the string can't be translated to a number then
		 * the exception NumberException is thrown */
		const double toDouble();
		/** Transforms the contents of the string to a long double
		 * if the string can't be translated to a number then
		 * the exception NumberException is thrown */
		const long double toLongDouble();
		/** Transforms the contents of the string to a Int64
		 * if the string can't be translated to a number then
		 * the exception NumberException is thrown */
		const Int64 toInt64();
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool operator==(const int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool operator==(const unsigned int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 *  to <b>buffer</b> */
		const bool operator==(const float n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool operator==(const double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool operator==(const long double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool operator==(const Int64 n);
		bool operator==(const String &s) const;
		/** Transforms and checks if the parameter <b>n</b> is not equal 
		 * to <b>buffer</b> */
		const bool operator!=(const int n);
		/** Transforms and checks if the parameter <b>n</b> is not equal 
		 * to <b>buffer</b> */
		const bool operator!=(const unsigned int n);
		/** Transforms and checks if the parameter <b>n</b> is not equal 
		 *  to <b>buffer</b> */
		const bool operator!=(const float n);
		/** Transforms and checks if the parameter <b>n</b> is not equal 
		 * to <b>buffer</b> */
		const bool operator!=(const double n);
		/** Transforms and checks if the parameter <b>n</b> is not equal 
		 * to <b>buffer</b> */
		const bool operator!=(const long double n);
		/** Transforms and checks if the parameter <b>n</b> is not equal 
		 * to <b>buffer</b> */
		const bool operator!=(const Int64 n);
		bool equals(const char c) const;
		bool equals(const char *s) const;
		bool equals(const String &s) const;
		virtual int compare(const String &s) const{
			return CharString::compare(s.buffer);
		}
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool equals(const int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool equals(const unsigned int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool equals(const float n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool equals(const double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool equals(const long double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		const bool equals(const Int64 n);

		/** Deletes the first character in <b>buffer</b> */
		const String &deleteFirst();
		/** Deletes the last character in <b>buffer</b> */
		const String &deleteLast();

		/** This method checks if the current string starts with the string
		 * stored in <b>s</b> without taking care if <b>s</b> is uppercase
		 * or no */
		bool startsIWith(const char *s) const;
		bool startsWith(const String &s) const;

		/** With this you can delete a character at a given position <b>pos</b>, 
		 * positions start at 0 */
		void deleteCharAt(const int pos);

		/** Use this method when you need to add a given character <b>c</b> at
		 * position <b>pos</b> */
		void insertCharAt(const int pos, const char c);
		/** Will return a substring contained between the specified limits
		 * \param start is the starting point to search for the begining of the substring
		 * \param end is the end of the substring, it should not exceed the length of the main string
		 * \note Since this is a newly created pointer please dont forget
		 * to free it after you use it while calling the Memory::freeBuffer
		 * method */
		char *getSubstr(int start, int end);
		virtual const std::string &toString();
};

};
#endif
