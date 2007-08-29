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
#ifndef __XVR2_STRING_H__
#define __XVR2_STRING_H__
#define __XVR2_ENABLE_BASIC_STRING__
#include<xvr2/BasicString.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	/** @brief The String class!!!
	 * This a string treatment class, it has a lot of methods and the
	 * main idea is eliminate de use of the common tricks we use everyday
	 * while we work with strings.
	 * Many times when we work with strings we leave BIG memory leaks
	 * in our programs, the main idea here is to help the programmer
	 * by providing here a very complete strig treatment tool for
	 * everyday use. */
	class String:public BasicString<char> {
		private:
		protected:
		public:
			/** @brief Mandatory Default constructor. */
			String();
			/** @brief Instantiates a String object by copying another.
			 *  @param s The String to be copied */
			String(const String &s);
			/** @brief Instantiates an String object by copying an array of 
			 *  characters.
			 *  @param s A null-terminated array of characters to be copied */
			String(const char *s);
			/** @brief Instantiates an String object from a numeric data-type.
			 *  This method will try to convert the given argument to a valid
			 *  string equivalent.
			 *  @param n An Int32 integer. */  
			String(const Int32 n);
			/** @brief Instantiates an String object from a numeric data-type.
			 *  This method will try to convert the given argument to a valid
			 *  string equivalent.
			 *  @param n An UInt32 integer. */
			String(const UInt32 n);
			/** @brief Instantiates an String object from a numeric data-type.
			 *  This method will try to convert the given argument to a valid
			 *  string equivalent.
			 *  @param n An Int64 integer. */
			String(const Int64 n);
			/** @brief Instantiates an String object from a numeric data-type.
			 *  This method will try to convert the given argument to a valid
			 *  string equivalent.
			 *  @param n An UInt64 integer. */
			String(const UInt64 n);
			/** @brief Instantiates an String object from a floating-point
			 *  data-type.
			 *  This method will try to convert the given argument to a valid
			 *  string equivalent.
			 *  @param n The float number. */
			String(const float n);
			/** @brief Instantiates an String object from a floating-point
			 *  data-type.
			 *  This method will try to convert the given argument to a valid
			 *  string equivalent.
			 *  @param n The double number. */
			String(const double n);
			/** @brief Instantiates an String object from a floating-point
			 *  data-type.
			 *  This method will try to convert the given argument to a valid
			 *  string equivalent.
			 *  @param n The long double number. */
			String(const long double n);
			/** @brief Instantiates a String object from a std::string object
			 *  @param s The String to be copied */
			String(const std::string &s);
			/** @brief Instantiates a String object from a std::string object
			 *  @param s The String to be copied */
			String(const std::string *s);
			String(const xvr2::Object &o);
			/** @brief Transforms the given argument and sets it to the current
			 *  String.
			 *  @param n The numeric value to be converted.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const Int32 n);
			/** @brief Transforms the given argument and sets it to the current
			 *  String.
			 *  @param n The numeric value to be converted.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const Int64 n);
			/** @brief Transforms the given argument and sets it to the current
			 *  String.
			 *  @param n The numeric value to be converted.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const UInt32 n);
			/** @brief Transforms the given argument and sets it to the current
			 *  String.
			 *  @param n The numeric value to be converted.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const UInt64 n);
			/** @brief Transforms the given argument and sets it to the current
			 *  String.
			 *  @param n The numeric value to be converted.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const float n);
			/** @brief Transforms the given argument and sets it to the current
			 *  String.
			 *  @param n The numeric value to be converted.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const double n);
			/** @brief Transforms the given argument and sets it to the current
			 *  String.
			 *  @param n The numeric value to be converted.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const long double n);
			/** @brief Replaces the contents of the String with the given
			 *  character.
			 *  @param c The character to use.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const char c);
			/** @brief Replaces the contents of the String with the given
			 *  array of characters.
			 *  @param sstr The array of characters to use.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const char *sstr);
			/** @brief Replaces the contents of the String with the contents of
			 *  the given std::string object.
			 *  @param s A pointer to a std::string object.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const std::string *s);
			/** @brief Replaces the contents of the String with the contents of
			 *  another String object
			 *  @param sstr A reference to the String to be copied.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &assign(const String &sstr);
			/** @brief Concatenates (appends) the given argument to the 
			 *  contents of the String.
			 *  @param s An array of characters
			 *  @return A reference to the current String object after
			 *  modified. */ 
			String &concat(const char *s);
			/** @brief Concatenates (appends) the given argument to the 
			 *  contents of the String.
			 *  @param c A single character.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const char c);
			/** @brief Concatenates (appends) the given argument to the 
			 *  contents of the String.
			 *  @param s An String.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const String &s);
			/** @brief Concatenates (appends) the given numeric argument (after
			 *  transforming it) to the contents of the String.
			 *  @param n An Int32 number.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const Int32 n);
			/** @brief Concatenates (appends) the given numeric argument (after
			 *  transforming it) to the contents of the String.
			 *  @param n An Int64 number.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const Int64 n);
			/** @brief Concatenates (appends) the given numeric argument (after
			 *  transforming it) to the contents of the String.
			 *  @param n An UInt32 number.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const UInt32 n);
			/** @brief Concatenates (appends) the given numeric argument (after
			 *  transforming it) to the contents of the String.
			 *  @param n An UInt64 number.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const UInt64 n);
			/** @brief Concatenates (appends) the given numeric argument (after
			 *  transforming it) to the contents of the String.
			 *  @param n A float number.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const float n);
			/** @brief Concatenates (appends) the given numeric argument (after
			 *  transforming it) to the contents of the String.
			 *  @param n A double number.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const double n);
			/** @brief Concatenates (appends) the given numeric argument (after
			 *  transforming it) to the contents of the String.
			 *  @param n A long double number.
			 *  @return A reference to the current String object after
			 *  modified. */
			String &concat(const long double n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const Int32 n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const UInt32 n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const Int64 n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const UInt64 n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const float n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const double n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const long double n);
			/** @brief Same as the String::assign methods.
			 *  @see String::assign. */
			String& operator=(const String &s);
			const String& operator+=(const String &s);
			/** @brief Same as the String::concat methods.
			 *  @see String::concat. */
			const String& operator+=(const Int32 n);
			/** @brief Same as the String::concat methods.
			 *  @see String::concat. */
			const String& operator+=(const UInt32 n);
			/** @brief Same as the String::concat methods.
			 *  @see String::concat. */
			const String& operator+=(const Int64 n);
			/** @brief Same as the String::concat methods.
			 *  @see String::concat. */
			const String& operator+=(const UInt64 n);
			/** @brief Same as the String::concat methods.
			 *  @see String::concat. */
			const String& operator+=(const float n);
			/** @brief Same as the String::concat methods.
			 *  @see String::concat. */
			const String& operator+=(const double n);
			/** @brief Same as the String::concat methods.
			 *  @see String::concat. */
			const String& operator+=(const long double n);
			/** @brief Lets you send the contents of a String an std::ostream.
			 *  This method allows you to do something like:
			 *  @code
			 *  String a = "hello world";
			 *  std::cout << a << std::endl;
			 *  @endcode
			 *  @param stream The std::ostream which is to receive the String
			 *  contents.
			 *  @param s The String to be sent.
			 *  @return A reference to the std::ostream object after modified.*/
			friend std::ostream& operator<<(std::ostream& stream, 
											const String &s);
			/** @brief Transforms all characters to uppercase.
			 *  @return A reference to the current String object after
			 *  modified. */
			const String& toUpperCase();
			/** @brief Transforms all characters to lowercase.
			 *  @return A reference to the current String object after
			 *  modified. */
			const String& toLowerCase();
			/** @brief Converts the string contents to an integer if possible.
			 *  @exception xvr2::NumberException if the String couldn't be
			 *  converted.
			 *  @return The converted integer. */
			const int toInt();
			/** @brief Converts the string contents to an unsigned integer
			 *  if possible.
			 *  @exception xvr2::NumberException if the String couldn't be
			 *  converted.
			 *  @return The converted unsigned integer. */
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
			/** @brief Same as the String::equals methods. */
			const bool operator==(const Int32 n);
			/** @brief Same as the String::equals methods. */
			const bool operator==(const UInt32 n);
			/** @brief Same as the String::equals methods. */
			const bool operator==(const Int64 n);
			/** @brief Same as the String::equals methods. */
			const bool operator==(const UInt64 n);
			/** @brief Same as the String::equals methods. */
			const bool operator==(const float n);
			/** @brief Same as the String::equals methods. */
			const bool operator==(const double n);
			/** @brief Same as the String::equals methods. */
			const bool operator==(const long double n);
			/** @brief Inequality operator, compares if the "textual" form of
			 *  the given argument is not the same as the String contents.
			 *  @param n An Int32 whose textual form will be used for 
			 *  comparison.
			 *  @return true If they are NOT equal, false if they are. */
			const bool operator!=(const Int32 n);
			/** @brief Inequality operator, compares if the "textual" form of
			 *  the given argument is not the same as the String contents.
			 *  @param n An UInt32 whose textual form will be used for 
			 *  comparison.
			 *  @return true If they are NOT equal, false if they are. */
			const bool operator!=(const UInt32 n);
			/** @brief Inequality operator, compares if the "textual" form of
			 *  the given argument is not the same as the String contents.
			 *  @param n An Int64 whose textual form will be used for 
			 *  comparison.
			 *  @return true If they are NOT equal, false if they are. */
			const bool operator!=(const Int64 n);
			/** @brief Inequality operator, compares if the "textual" form of
			 *  the given argument is not the same as the String contents.
			 *  @param n An UInt64 whose textual form will be used for 
			 *  comparison.
			 *  @return true If they are NOT equal, false if they are. */
			const bool operator!=(const UInt64 n);
			/** @brief Inequality operator, compares if the "textual" form of
			 *  the given argument is not the same as the String contents.
			 *  @param n A float whose textual form will be used for 
			 *  comparison.
			 *  @return true If they are NOT equal, false if they are. */
			const bool operator!=(const float n);
			/** @brief Inequality operator, compares if the "textual" form of
			 *  the given argument is not the same as the String contents.
			 *  @param n A double whose textual form will be used for 
			 *  comparison.
			 *  @return true If they are NOT equal, false if they are. */
			const bool operator!=(const double n);
			/** @brief Inequality operator, compares if the "textual" form of
			 *  the given argument is not the same as the String contents.
			 *  @param n A long double whose textual form will be used for 
			 *  comparison.
			 *  @return true If they are NOT equal, false if they are. */
			const bool operator!=(const long double n);
			/** @brief Performs a lexicographic comparison between two String.
			 *  @param s The String to be compared with.
			 *  @return 0 if their contents are the same, less than zero if
			 *  if the current String length is less than the lenght of s, in
			 *  any other case returns a positive number. */
			int compare(const String &s) const;
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param c A character to be compared with.
			 *  @return true if both are equal, false if not. */
			bool equals(const char c) const;
			/** @brief Tells wheter two String have the same contents
			 *  @param s A String to be compared with.
			 *  @return true if both are equal, false if not. */
			bool equals(const String &s) const;
			/** @brief Tells wheter two String have the same contents
			 *  @param s A String to be compared with.
			 *  @return true if both are equal, false if not. */
			bool equals(const String &s);
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param n An Int32 to be compared with.
			 *  @return true if both are equal, false if not. */
			const bool equals(const Int32 n);
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param n An UInt32 to be compared with.
			 *  @return true if both are equal, false if not. */
			const bool equals(const UInt32 n);
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param n An Int64 to be compared with.
			 *  @return true if both are equal, false if not. */
			const bool equals(const Int64 n);
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param n An UInt64 to be compared with.
			 *  @return true if both are equal, false if not. */
			const bool equals(const UInt64 n);
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param n A float to be compared with.
			 *  @return true if both are equal, false if not. */
			const bool equals(const float n);
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param n A double to be compared with.
			 *  @return true if both are equal, false if not. */
			const bool equals(const double n);
			/** @brief Verifies if the String contents are the same as textual
			 *  form of the given argument.
			 *  @param n A long double to be compared with.
			 *  @return true if both are equal, false if not. */
			const bool equals(const long double n);
			/** @brief Tells if the string starts with the given substring 
			 *  regardless of its case (upper or lower).
			 *  @param s substring to look at the beginning.
			 *  @return true if the string starts with the specified substring,
			 *  false otherwise. */
			bool startsIWith(const char *s) const;
			/** @brief Tells if the string starts with the given substring
			 *  taking care that each character case matches.
			 *  @param s substring to look at the beginning.
			 *  @return true if the string starts with the specified substring,
			 *  false otherwise. */
			bool startsWith(const String &s) const;
			/** @brief Tells if the string ends with the given substring
			 *  regardless of its case (upper or lower).
			 *  @param s substring to look at the end.
			 *  @return true if the string ends with the specified substring,
			 *  false otherwise. */
			bool endsIWith(const char *s) const;
			/** @brief Tells if the string ends with the given substring
			 *  taking care that each character case matches.
			 *  @param s substring to look at the end.
			 *  @return true if the string ends with the specified substring,
			 *  false otherwise. */
			bool endsWith(const String &s) const;
			/** @brief Lets you retrieve a substring from the current string.
			 *  @param start The position where the initial part of the 
			 *  substring we want to extract is located at.
			 *  @param end The position at where the last character from our
			 *  substring is located at.
			 *  @return The extracted substring. */
			String getSubstr(int start, int end);
			/** @brief Converts this String to a std::string.
			 *  @return A std:string equivalent to this String. */
			virtual std::string toString();
			/** @brief Will append an arbitrary amount characters from the 
			 *  given array.
			 *  @param data The array from where we will be copying,
			 *  @param len The amount of chars to be copied from there. */
			void eat(const char *data, int len);
			/** @brief Erases all contiguous occurrences of a specified 
			 *  character from the beginning of the string to the right.
			 *  @param c The character to look for and erase.
			 *  @return A reference to string after modified. */
			virtual String &trimLeft(const char c = ' ');
			/** @brief Erases all contiguous occurrences of a specified 
			 *  character from the end of the string to the left.
			 *  @param c The character to look for and erase.
			 *  @return A reference to string after modified. */
			virtual String &trimRight(const char c = ' ');
	};
	extern const String NL;
};
#endif
