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
#ifndef __XVR2_ENABLE_BASIC_STRING__
#error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif
#ifndef __XVR2_BASIC_STRING_H__
#define __XVR2_BASIC_STRING_H__
#include<xvr2/Object.h>
#include<xvr2/CoreExceptions.h>
#include<string>

namespace xvr2 {
	/** @brief Abstract string base class. */
	template<class _charT>
	class BasicString : public Object, public std::basic_string<_charT> {
		protected:
			BasicString(){
			}
			BasicString(const _charT *s){
				std::basic_string<_charT>::assign(s);
			}
		public:
			~BasicString(){}
			/** @brief Returns the location (from left to right) of the first 
			 *  ocurrence of s.
			 *  @param s The substring to search for.
			 *  @return The position where the substring is or 
			 *  BasicString::npos if the substring was not contained in the
			 *  string itself. */
			virtual int index(const _charT *s){
				return std::basic_string<_charT>::find(s);
			}
			/** @brief Returns the location (from left to right) of the first 
			 *  ocurrence of s.
			 *  @param s The substring to search for.
			 *  @return The position where the substring is or 
			 *  BasicString::npos if the substring was not contained in the
			 *  string itself. */
			virtual int index(const _charT *s) const{
				return std::basic_string<_charT>::find(s);
			}
			/** @brief Returns the location (from left to right) of the first 
			 *  ocurrence of s.
			 *  @param s The substring to search for.
			 *  @return The position where the substring is or 
			 *  BasicString::npos if the substring was not contained in the
			 *  string itself. */
			virtual int index(const BasicString<_charT> &s){
				return std::basic_string<_charT>::find(s.c_str());
			}
			/** @brief Returns the location (from right to left) of the first 
			 *  ocurrence of s.
			 *  @param s The substring to search for.
			 *  @return The position where the substring is or 
			 *  BasicString::npos if the substring was not contained in the
			 *  string itself. */
			virtual int rindex(const _charT *s){
				return std::basic_string<_charT>::find_last_of(s);
			}
			/** @brief Returns the location (from right to left) of the first 
			 *  ocurrence of s.
			 *  @param s The substring to search for.
			 *  @return The position where the substring is or 
			 *  BasicString::npos if the substring was not contained in the
			 *  string itself. */
			virtual int rindex(const _charT *s) const{
				return std::basic_string<_charT>::find_last_of(s);
			}
			/** @brief Returns the location (from right to left) of the first 
			 *  ocurrence of s.
			 *  @param s The substring to search for.
			 *  @return The position where the substring is or 
			 *  BasicString::npos if the substring was not contained in the
			 *  string itself. */
			virtual int rindex(const BasicString<_charT> &s){
				return std::basic_string<_charT>::find_last_of(s.c_str());
			}
			/** @brief Erases an amount of characters starting from the left. 
			 *  @param howmany The amount of chars to be deleted from the
			 *  beginning of the string.
			 *  @return A reference to string after modified. */
			BasicString<_charT> &biteLeft(UInt32 howmany = 1){
				if(std::basic_string<_charT>::size() == howmany){
					std::basic_string<_charT>::clear();
				}
				else{
					std::basic_string<_charT>::erase(
							std::basic_string<_charT>::begin(), 
							std::basic_string<_charT>::begin() + howmany
							);
				}
				return *this;
			}
			/** @brief Erases an amount of characters starting from right 
			 *  to left. 
			 *  @param howmany The amount of chars to be deleted from the
			 *  the last portions of the string backwards.
			 *  @return A reference to string after modified. */
			BasicString<_charT> &biteRight(UInt32 howmany = 1){
				if(std::basic_string<_charT>::size() == howmany){
					std::basic_string<_charT>::clear();
				}
				else{
					std::basic_string<_charT>::erase(
							std::basic_string<_charT>::end() - howmany, 
							std::basic_string<_charT>::end()
							);
				}
				return *this;
			}
			/** @brief Erases the first character from the string itself.
			 *  @return A reference to string after modified. */
			BasicString<_charT> &deleteFirst(){
				return biteLeft(1);
			}
			/** @brief Erases the last character from the string itself.
			 *  @return A reference to string after modified. */
			BasicString<_charT> &deleteLast(){
				return biteRight(1);
			}
			/** @brief Erases all contiguous occurrences of a specified 
			 *  character from the beginning of the string to the right.
			 *  @param c The character to look for and erase.
			 *  @return A reference to string after modified. */
			virtual BasicString<_charT> &trimLeft(const _charT c = ' '){
				while(std::basic_string<_charT>::size() > 0 && 
						std::basic_string<_charT>::at(0) == c){
					std::basic_string<_charT>::erase(
							std::basic_string<_charT>::begin(), 
							std::basic_string<_charT>::begin() + 1
							);
				}
				return *this;
			}
			/** @brief Erases all contiguous occurrences of a specified 
			 *  character from the end of the string to the left.
			 *  @param c The character to look for and erase.
			 *  @return A reference to string after modified. */
			virtual BasicString<_charT> &trimRight(const _charT c = ' '){
				while(std::basic_string<_charT>::size() > 0 && 
						std::basic_string<_charT>::at(std::basic_string<_charT>::size() - 1) == c){
					std::basic_string<_charT>::erase(
							std::basic_string<_charT>::end() - 1, 
							std::basic_string<_charT>::end()
							);
				}
				return *this;
			}
			/** @brief Combines BasicString::trimLeft and 
			 *  BasicString::trimRight.
			 *  @param c The character to look for and erase.
			 *  @return A reference to string after modified. */
			virtual BasicString<_charT> &trim(const _charT c = ' '){
				trimLeft(c);
				trimRight(c);
				return *this;
			}
			/** @brief Verifies if the string is EXACTLY the same as the given
			 *  argument.
			 *  @param s The string to be compared with.
			 *  @return true if both are the same, false if not. */
			virtual bool equals(const _charT *s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** @brief Verifies if the string is EXACTLY the same as the given
			 *  argument.
			 *  @param s The string to be compared with.
			 *  @return true if both are the same, false if not. */
			virtual bool equals(const BasicString<_charT> &s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** @brief Verifies if the string is EXACTLY the same as the given
			 *  argument.
			 *  @param s The string to be compared with.
			 *  @return true if both are the same, false if not. */
			virtual bool equals(const BasicString<_charT> &s) const{
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** @brief Verifies if the string is EXACTLY the same as the given
			 *  argument.
			 *  @param s The string to be compared with.
			 *  @return true if both are the same, false if not. */
			virtual bool operator==(const _charT *s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** @brief Verifies if the string is EXACTLY the same as the given
			 *  argument.
			 *  @param s The string to be compared with.
			 *  @return true if both are the same, false if not. */
			virtual bool operator==(const BasicString<_charT> &s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** @brief Deletes the string contents. */
	 		void deleteString(){
				std::basic_string<_charT>::clear();
			}
			/** @brief Converts the string to an array of characters.
			 *  @returns A const pointer to the internal character array. */
			const _charT *toCharPtr() const {
				return std::basic_string<_charT>::c_str();
			}
			/** @brief Converts the string to an array of characters.
			 *  @returns A const pointer to the internal character array. */
			const _charT *toCharPtr(){
				return std::basic_string<_charT>::c_str();
			}
			/** @brief Gets the character located at the given position.
			 *  @param i The position where the requested character is 
			 *  located at. 
			 *  @return the character at given position i. */
			const _charT charAt(int i) const {
				return std::basic_string<_charT>::at(i);
			}
			/** @brief Gets the character located at the given position.
			 *  @param i The position where the requested character is 
			 *  located at. 
			 *  @return the character at given position i. */
			const _charT charAt(int i) {
				return std::basic_string<_charT>::at(i);
			}
			/** @brief Gets the character located at the given position.
			 *  @param i The position where the requested character is 
			 *  located at. 
			 *  @return the character at given position i. */
			const _charT operator[](int i){
				return std::basic_string<_charT>::at(i);
			}
			/** @brief Gets the character located at the given position.
			 *  @param i The position where the requested character is 
			 *  located at. 
			 *  @return the character at given position i. */
			const _charT operator[](int i) const {
				return std::basic_string<_charT>::at(i);
			}
			/** @brief Tells if the string starts with the given substring
			 *  @param s substring to look at the beginning.
			 *  @return true if the string starts with the specified substring,
			 *  false otherwise. */
			bool startsWith(const _charT *s) const {
				return (std::basic_string<_charT>::find(s) == 0)?true:false;
			}
			/** @brief Tells if the string ends with the given substring
			 *  @param s substring to look at the end.
			 *  @return true if the string ends with the specified substring,
			 *  false otherwise. */
			bool endsWith(const _charT *s) const {
				std::basic_string<_charT> tmp = s;
				//return (std::basic_string<_charT>::size() - (std::basic_string<_charT>::find_last_of(s) + tmp.size()) == 0)?true:false;
				return (std::basic_string<_charT>::size() - 
						(std::basic_string<_charT>::find_last_of(s) + 1) 
						== 0)?true:false;
			}
			/** @brief Erases a character at the given position.
			 *  @param pos The position (from left to right) where the character
			 *  we want to delete is located at.
			 *  @return A reference to the string after modified. */
			BasicString<_charT> &deleteCharAt(int pos){
				std::basic_string<_charT>::erase(pos);
				return *this;
			}
			/** @brief Insert a specifig character at the given position.
			 *  @param pos The position at where we want to place the character
			 *  @param c The character we want to insert.
			 *  @return A reference to the string after modified. */
			BasicString<_charT> &insertCharAt(const int pos, const _charT c) {
				std::string::insert(pos, 1, c);
				return *this;
			}
			/** @brief Lets you retrieve a substring from the current string.
			 *  @param start The position where the initial part of the 
			 *  substring we want to extract is located at.
			 *  @param end The position at where the last character from our
			 *  substring is located at.
			 *  @return The extracted substring. */
			BasicString<_charT> getSubstr(int start, int end){
				return BasicString<_charT>::substr(start, end);
			}
			/** @brief Replaces all occurrences of a character with the given
			 *  character array.
			 *  @param from The character we wish to replace.
			 *  @param to The array of characters wish will be used as 
			 *  replacement. 
			 *  @return A reference to the string after modified. */
			BasicString<_charT> &replace(const _charT from, const _charT *to){
				for(unsigned int i = 0; i < std::basic_string<_charT>::size(); i++){
					if(charAt(i) == from){
						std::basic_string<_charT>::erase(i, 1);
						std::basic_string<_charT>::insert(i, to);
						i++;
					}
				}
				return *this;
			}
	};
};
#endif
