/*
 * $Id$
 */
#ifndef __XVR2_ENABLE_BASIC_STRING__
#error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif
#ifndef __XVR2_BASIC_STRING_H__
#define __XVR2_BASIC_STRING_H__
#include<xvr2/Object.h>
#include<xvr2/_xvr2ClassNames.h>
#include<xvr2/CoreExceptions.h>
#if __GNUC__ < 3
#include<string.h>
#else
#include<string>
#endif

namespace xvr2 {
	template<class _charT>
	class BasicString : public Object, public std::basic_string<_charT> {
		protected:
			BasicString(){
#ifdef USE_EMBEDDED_CLASSNAMES
				setClassName(BasicString);
#endif
			}
			BasicString(const _charT *s){
#ifdef USE_EMBEDDED_CLASSNAMES
				setClassName(BasicString);
#endif
				std::basic_string<_charT>::assign(s);
			}
		public:
			~BasicString(){}
			/** Returns the location (from left to right) of the first ocurrence of s */
			virtual int index(const _charT *s){
				return std::basic_string<_charT>::find(s);
			}
			/** Returns the location (from left to right) of the first ocurrence of s */
			virtual int index(const _charT *s) const{
				return std::basic_string<_charT>::find(s);
			}
			/** Returns the location (from left to right) of the first ocurrence of s */
			virtual int index(const BasicString<_charT> &s){
				return std::basic_string<_charT>::find(s.c_str());
			}
			/** Returns the last location (from left to right) of the first ocurrence of s */
			virtual int rindex(const _charT *s){
				return std::basic_string<_charT>::find_last_of(s);
			}
			/** Returns the last location (from left to right) of the first ocurrence of s */
			virtual int rindex(const _charT *s) const{
				return std::basic_string<_charT>::find_last_of(s);
			}
			/** Returns the last location (from left to right) of the first ocurrence of s */
			virtual int rindex(const BasicString<_charT> &s){
				return std::basic_string<_charT>::find_last_of(s.c_str());
			}
			/** Erases howmany characters from the left of the string */
			BasicString<_charT> &biteLeft(int howmany = 1){
				std::basic_string<_charT>::erase(std::basic_string<_charT>::begin(), std::basic_string<_charT>::begin() + howmany);
				return *this;
			}
			/** Erases howmany characters from the right side of the string */
			BasicString<_charT> &biteRight(int howmany = 1){
				std::basic_string<_charT>::erase(std::basic_string<_charT>::end() - howmany, std::basic_string<_charT>::end());
				return *this;
			}
			BasicString<_charT> &deleteFirst(){
				return biteLeft(1);
			}
			BasicString<_charT> &deleteLast(){
				return biteRight(1);
			}
			/** Erases all ocurrences of character c located at the left side of the string */
			virtual BasicString<_charT> &trimLeft(const _charT c = ' '){
				while(std::basic_string<_charT>::size() > 0 && std::basic_string<_charT>::at(0) == c){
					//std::basic_string<_charT>::erase(0);
					std::basic_string<_charT>::erase(std::basic_string<_charT>::begin(), std::basic_string<_charT>::begin() + 1);
				}
				return *this;
			}
			/** Erases all ocurrences of character c located at the right side of the string */
			virtual BasicString<_charT> &trimRight(const _charT c = ' '){
				while(std::basic_string<_charT>::size() > 0 && std::basic_string<_charT>::at(std::basic_string<_charT>::size() - 1) == c){
					//std::basic_string<_charT>::erase(std::basic_string<_charT>::size() - 1);
					std::basic_string<_charT>::erase(std::basic_string<_charT>::end() - 1, std::basic_string<_charT>::end());
				}
				return *this;
			}
			/** Erases all ocurrences of character c located at the right and left side of the string */
			virtual BasicString<_charT> &trim(const _charT c = ' '){
				trimLeft(c);
				trimRight(c);
				return *this;
			}
			/** Returns true if the string is exactly the same as s */
			virtual bool equals(const _charT *s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** Returns true if the string is exactly the same as s */
			virtual bool equals(const BasicString<_charT> &s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** Returns true if the string is exactly the same as s */
			virtual bool equals(const BasicString<_charT> &s) const{
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** Returns true if the string is exactly the same as s */
			virtual bool operator==(const _charT *s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** Returns true if the string is exactly the same as s */
			virtual bool operator==(const BasicString<_charT> &s){
				return (std::basic_string<_charT>::compare(s) == 0)?true:false;
			}
			/** Deletes the string contents */
	 		void deleteString(){
				std::basic_string<_charT>::clear();
			}
			/** Returns a const pointer to the internal character array data stored */
			const _charT *toCharPtr() const {
				return std::basic_string<_charT>::c_str();
			}
			/** Returns a const pointer to the internal character array data stored */
			const _charT *toCharPtr(){
				return std::basic_string<_charT>::c_str();
			}
			/** Return the character contained at position i (from left to right) */
			const _charT charAt(int i) const {
				return std::basic_string<_charT>::at(i);
			}
			/** Return the character contained at position i (from left to right) */
			const _charT charAt(int i) {
				return std::basic_string<_charT>::at(i);
			}
			/** Return the character contained at position i (from left to right) */
			const _charT operator[](int i){
				return std::basic_string<_charT>::at(i);
			}
			/** Return the character contained at position i (from left to right) */
			const _charT operator[](int i) const {
				return std::basic_string<_charT>::at(i);
			}
			//virtual bool startsIWith(const _charT *s) const = 0;
			bool startsWith(const _charT *s) const {
				return (std::basic_string<_charT>::find(s) == 0)?true:false;
			}
			//virtual bool endsIWith(const _charT *s) const = 0;
			bool endsWith(const _charT *s) const {
				std::basic_string<_charT> tmp = s;
				//return (std::basic_string<_charT>::size() - (std::basic_string<_charT>::find_last_of(s) + tmp.size()) == 0)?true:false;
				return (std::basic_string<_charT>::size() - (std::basic_string<_charT>::find_last_of(s) + 1) == 0)?true:false;
			}
			BasicString<_charT> &deleteCharAt(int pos){
				std::basic_string<_charT>::erase(pos);
				return *this;
			}
			BasicString<_charT> &insertCharAt(const int pos, const _charT c) {
				std::string::insert(pos, 1, c);
				return *this;
			}
			BasicString getSubstr(int start, int end){
				return BasicString<_charT>::substr(start, end);
			}
			/** Replaces all ocurrences of the string from with the contents of the
			 *  string to. */
			BasicString<_charT> replace(const _charT from, const _charT *to){
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
