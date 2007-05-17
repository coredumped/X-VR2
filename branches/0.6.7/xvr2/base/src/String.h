/*
 $Id$
 */
#ifndef __XVR2_STRING_H__
#define __XVR2_STRING_H__
#include<System.h>
#include<StringException.h>
#include<InvalidParameterException.h>
#include<ArrayIndexOutOfLimitsException.h>
#include<BufferTooSmall.h>
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
class String:public System{
	private:
		/** Holds the string itself as and array of chars by default it points
		 *  to <b>0x0</b> which also means empty <b>String</b> */
		char *buffer;
		/** Holds the dimensions of the string plus one, the reserved address 
		 *  is for storing the termination character <b>0x0</b> */
		int len;
		/** Eliminates the contents of buffer and sets len to zero */
		void destroy();
	protected:
	public:
		/** Default constructor, it initializes buffer and len to zero */
		String();
		/** \fn String(String &s)
		 *  This constructor initializes an instance of this class
		 *  by taking a another reference of the same class as
		 *  parameter
		 *  \param s is the String to be copied */
		String(String &s);
		/** This constructor initializes an instance of this class
		 *  by taking an array of chars */
		String(const char *s);
		/** This constructor initializes an instance of this class
		 *  by transforming an integer to an array of chars and
		 *  then calling assign(const char *s); */
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
		/** Destructor, eliminates the contents of buffer and
		 *  sets len to zero by calling the method destroy(); */
		~String();
		/** Assigns the contents of <b>s</b> to buffer */
		void assign(const char *s);
		/** Transforms and assigns <b>n</b> to the current String */
		void assign(const int n);
		/** Transforms and assigns <b>n</b> to the current String */
		void assign(const unsigned int n);
		/** Transforms and assigns <b>n</b> to the current String */
		void assign(const float n);
		/** Transforms and assigns <b>n</b> to the current String */
		void assign(const double n);
		/** Transforms and assigns <b>n</b> to the current String */
		void assign(const long double n);
		/** Transforms and assigns <b>n</b> to the current String */
		void assign(const Int64 n);
		/** replaces the contents of the string with sstr */
		void assign(const String &sstr);
		/** Returns a C char * representation of this String, please
		 *  do dot delete or free the memory used by this pointer,
		 *  this class's destructor will take care of the proper
		 *  memory cleanup.
		 *  \return A C char * equivalent to the data stored in this
		 *  object. */
		char *toCharPtr() const ;
		/** transforms and concatenates s to the current String */
		void concat(const char *s);
		/** transforms and concatenates s to the current String */
		void concat(const char c);
		/** transforms and concatenates s to the current String */
		void concat(String &s);
		/** Transforms and concatenates n to the current String */
		void concat(const int n);
		/** transforms and concatenates n to the current String */
		void concat(const unsigned int n);
		/** transforms and concatenates n to the current String */
		void concat(const float n);
		/** transforms and concatenates n to the current String */
		void concat(const double n);
		/** transforms and concatenates n to the current String */
		void concat(const long double n);
		/** transforms and concatenates n to the current String */
		void concat(const Int64 n);
		/** transforms and concatenates n to the current String */
		void concat(const UInt64 n);
		/** Assigns s to buffer by calling assign(const char *); */
		String& operator=(const char *s);
		/** Transforms n and assigns it to buffer by calling 
		 *  assign(const char *); */
		String& operator=(const int n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		String& operator=(const unsigned int n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		String& operator=(const float n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		String& operator=(const double n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		String& operator=(const long double n);
		/** Transforms n and assigns it to buffer by calling 
		 * assign(const char *); */
		String& operator=(const Int64 n);
		//String& operator=(const String &s);
		/** Concatenates s to the current String by 
		 * overriding the + operator returning an instance 
		 * of itself */
		String& operator+(String &s);
		/** Concatenates s to the current String by 
		 * overriding the + operator returning an instance 
		 * of itself */
		String& operator+(const char *s);
		/** Transforms and concatenates n to the current 
		 * String by overriding the + operator
		 * returning an instance of itself */
		String& operator+(const int n);
		/** Transforms and concatenates n to the current 
		 * String by overriding the + operator
		 * returning an instance of itself */
		String& operator+(const unsigned int n);
		/** Transforms and concatenates n to the current 
		 * String by overriding the + operator
		 * returning an instance of itself */
		String& operator+(const float n);
		/** Transforms and concatenates n to the current 
		 * String by overriding the + operator
		 * returning an instance of itself */
		String& operator+(const double n);
		/** Transforms and concatenates n to the current 
		 * String by overriding the + operator
		 * returning an instance of itself */
		String& operator+(const long double n);
		/** Transforms and concatenates n to the current 
		 * String by overriding the + operator
		 * returning an instance of itself */
		String& operator+(const Int64 n);
		/** Transforms and concatenates n to the current 
		 * String by overriding the + operator
		 * returning an instance of itself */
		String& operator+(const UInt64 n);
		/** Concatenates <b>s</b> to itself */
		String& operator+=(String &s);
		/** Concatenates <b>s</b> to itself */
		String& operator+=(const char *s);
		/** Transforms <b>n</b> and concatenates it to the current String */
		String& operator+=(const int n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		String& operator+=(const unsigned int n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		String& operator+=(const float n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		String& operator+=(const double n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		String& operator+=(const long double n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		String& operator+=(const Int64 n);
		/** Transforms <b>n</b> and concatenates it to the current String */
		String& operator+=(const UInt64 n);
		/** The main idea behind this is take advantage of the
		 * << operator of the ostream class, this way, you can
		 * use this class with streams<br>
		 * <b>String a = "hello world";</b><br>
		 * you would normally do:<br>
		 * <b>cout << a.toCharPtr() << endl;</b><br>
		 * with this operator you can just:<br>
		 * <b>cout << a << endl;</b> */
		friend std::ostream& operator<<(std::ostream& stream, String s);
		/** Returns the character at position i */
		const char charAt(int i);
		/** Returns the character at position i by overriding
		 * the operator[] */
		const char operator[](int i);
		/** This just calls destroy, so you can delete the
		 * contents in buffer without the need of delete
		 * the object itself */
 		void deleteString();
		/** Eliminates all ocurrences of the c character that
		 * appears at left of the string */
		String& trimLeft(const char c = ' ');
		/** Eliminates all ocurrences of the c character that
		 * appears at right of the string */
		String& trimRight(const char c = ' ');
		/** Eliminates all ocurrences of the c character that
		 * appears at the beginning and the end of the string */
		String& trim(const char c = ' ');
		/** Transforms the string to uppercase letters only */
		String& toUpperCase();
		/** Transforms the string to lowercase letters only */
		String& toLowerCase();
		/** Returns the lenght of the string which is stored
		 * in len */
		const unsigned int lenght();
		/** Returns the lenght of the string which is stored
		 * in len */
		const unsigned int size();
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
		/** Checks if the parameter <b>s</b> is equal to <b>buffer</b> */
		bool operator==(const String &s);
		/** Checks if the parameter <b>s</b> is equal to <b>buffer</b> */
		bool operator==(const char *s);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool operator==(const int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool operator==(const unsigned int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 *  to <b>buffer</b> */
		bool operator==(const float n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool operator==(const double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool operator==(const long double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool operator==(const Int64 n);
		/** Checks if the parameter <b>s1</b> is equal to <b>s2</b> */
		static bool equals(const String &s1, const String &s2);

		/** Checks if the parameter <b>s</b> is equal to <b>buffer</b> */
		bool equals(const char *s);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool equals(const int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool equals(const unsigned int n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool equals(const float n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool equals(const double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool equals(const long double n);
		/** Transforms and checks if the parameter <b>n</b> is equal 
		 * to <b>buffer</b> */
		bool equals(const Int64 n);
		/** Checks if the String <b>s</b> is equal to the <b>buffer</b>
		 * contained within this String object.
		 * \param s The String to compare with.  */
		bool equals(const String &s);

		/** Tells if the substring <b>s</b> is inside the current String */
		bool hasSubstring(String &s);
		/** Tells if the substring <b>s</b> is inside the current String */
		bool hasSubstring(const char *s);

		/** Deletes the first character in <b>buffer</b> */
		String &deleteFirst();
		/** Deletes the last character in <b>buffer</b> */
		String &deleteLast();

		/** Returns the leftmost position for string <b>s</b> inside buffer
		 * starting at byte <b>start</b> */
		const int index(const char *s, int start = 0);
		/** Returns the leftmost position for string <b>s</b> inside buffer
		 * starting at byte <b>start</b> */
		const int index(const String &s, int start = 0);
		/** Returns the leftmost position for string <b>s</b> inside buffer
		 * starting at byte <b>start</b> */
		const int index(const char c, int start = 0);

		/** Returns the rightmost position for string <b>s</b> inside buffer
		 * starting at byte <b>end</b> from right to left */
		const int rindex(const char *s, int end = 0);
		/** Returns the rightmost position for string <b>s</b> inside buffer
		 * starting at byte <b>end</b> from right to left */
		const int rindex(const String &s, int end = 0);
		/** Returns the rightmost position for string <b>s</b> inside buffer
		 * starting at byte <b>end</b> from right to left */
		const int rindex(const char c, int end = 0);

		/** This method checks if the current string starts with the string
		 * stored in <b>s</b> */
		bool startsWith(String &s);
		/** This method checks if the current string starts with the string
		 * stored in <b>s</b> */
		bool startsWith(const char *s);
		/** This method checks if the current string starts with the string
		 * stored in <b>s</b> without taking care if <b>s</b> is uppercase
		 * or no */
		bool startsIWith(const char *s);
		/** This method checks if the current string ends with the string
		 * stored in <b>s</b> */
		bool endsWith(String &s);
		/** This method checks if the current string ends with the string
		 * stored in <b>s</b> */
		bool endsWith(const char *s);

		/** With this you can delete a character at a given position <b>pos</b>, 
		 * positions start at 0 */
		String &deleteCharAt(const int pos);

		/** Use this method when you need to add a given character <b>c</b> at
		 * position <b>pos</b> */
		String &insertCharAt(const int pos, const char c);
		/** Will return a substring contained between the specified limits
		 * \param start is the starting point to search for the begining of the substring
		 * \param end is the end of the substring, it should not exceed the length of the main string
		 * \note Since this is a newly created pointer please dont forget
		 * to free it after you use it while calling the Memory::freeBuffer
		 * method */
		char *getSubstr(unsigned int start, unsigned int end);
};

};
#endif
