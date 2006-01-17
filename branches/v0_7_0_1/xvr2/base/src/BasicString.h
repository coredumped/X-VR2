/*
 * $Id$
 */
#ifndef __XVR2_ENABLE_BASIC_STRING__
#error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif
#ifndef __XVR2_BASIC_STRING_H__
#define __XVR2_BASIC_STRING_H__
#include<xvr2/Object.h>
#include<xvr2/ArrayIndexOutOfLimitsException.h>

namespace xvr2 {
	template<class CharT>
	class BasicString:public Object {
		protected:
			/** Holds the string itself as and array of chars by default it points
			 *  to <b>0x0</b> which also means empty <b>String</b> */
			CharT *buffer;
			/** Holds the dimensions of the string plus one, the reserved address 
			 *  is for storing the termination character <b>0x0</b> */
			int len;
			virtual void destroy(){
				if(buffer != 0){
					delete[] buffer;
				}
				buffer = 0;
				len = 0;
			}
			virtual int getlen(const CharT *s) const{
				int l;
				if(s == 0) return 0;
				for(l = 0; s[l] != 0; l++);
				return l;
			}
			virtual const CharT *copy(CharT *in, const CharT *s, int l, int in_offset = 0, int s_offset = 0){
				int i;
				if(l == 0 || s == 0)
					return in;
				for(i = 0; i < l; i++)
					in[in_offset + i] = s[i + s_offset];
				in[in_offset + i] = 0;
				return in;
			}
			virtual CharT *duplicate(const CharT *s, int l){
				CharT *c;
				int i;
				if(l == 0 || s == 0){
					c = new CharT[1];
					c[0] = 0;
					return c;
				}
				c = new CharT[l + 1];
				for(i = 0; i < l; i++)
					c[i] = s[i];
				c[i] = 0;
				return c;
			}
		public:
			BasicString(){
				CharT *c;
				c = new CharT[1];
				c[0] = 0;
				buffer = c;
				len = 0;
			}
			BasicString(const CharT *s){
				buffer = 0;
				len = 0;
				assign(s);
			}
			BasicString(const BasicString<CharT> &s){
				buffer = 0;
				len = 0;
				assign(s);
			}
			virtual ~BasicString(){
				destroy();
			}
			void assign(const CharT *s){
				if(buffer != 0){
					delete[] buffer;
				}
				len = getlen(s);
				buffer = duplicate(s, len);
			}
			void assign(const CharT c){
				if(buffer != 0){
					delete[] buffer;
				}
				buffer = new CharT[2];
				buffer[0] = c;
				buffer[1] = 0;
				len = 1;
			}
			void assign(const BasicString<CharT> &s){
				if(buffer != 0){
					delete[] buffer;
				}
				buffer = duplicate(s.buffer, s.len);
				len = s.len;
			}
			void concat(const CharT c){
				CharT *tmp;
				if(c == 0) return;
				if(buffer != 0){
					tmp = new CharT[len + 2];
					copy(tmp, buffer, len);
					tmp[len] = c;
					tmp[len + 1] = 0;
					delete[] buffer;
					buffer = tmp;
					len++;
				}
				else{
					buffer = new CharT[2];
					buffer[0] = c;
					buffer[1] = 0;
					len = 1;
				}
			}
			void concat(const CharT *s){
				CharT *tmp;
				int l2;
				if(buffer != 0){
					l2 = getlen(s);
					if(l2 > 0){
						tmp = new CharT[len + l2 + 1];
						copy(tmp, buffer, len);
						copy(tmp, s, l2, len);
						delete[] buffer;
						len = len + l2;
						buffer = tmp;
					}
				}
				else{
					assign(s);
				}
			}
			/*void concat(const BasicString<CharT> &s){
				CharT *tmp;
				if(buffer != 0){
					tmp = new CharT[len + s.len + 1];
					copy(tmp, buffer, len);
					copy(tmp, s.buffer, s.len, len);
					delete[] buffer;
					len = len + s.len + 1;
					buffer = tmp;
				}
				else{
					assign(s);
				}
			}*/
			const CharT operator[](int i) const{
				return charAt(i);
			}
			const CharT charAt(int i) const{
				if(buffer == 0 || i >= len || i < 0)
					throw xvr2::Exception::ArrayIndexOutOfLimits();
				return buffer[i];
			}
			CharT *toCharPtr() const {
				return buffer;
			}
 			virtual void deleteString(){
				if(buffer != 0){
					delete[] buffer;
					len = 0;
					buffer = 0;
				}
			}
			const void clear(){
				deleteString();
			}
			inline int length() const{
				return len;
			}
			inline int size() const{
				return len;
			}
			virtual inline bool equals(const CharT c) const{
				return (len == 1 && buffer[0] == c)?true:false;
			}
			virtual inline bool equals(const CharT *s) const{
				return (compare(s) == 0)?true:false;
			}
			virtual inline bool equals(const BasicString<CharT> &s) const{
				return (compare(s.buffer) == 0)?true:false;
			}
			virtual int compare(const CharT *c) const{
				int i;
				int l2;
				if(buffer == 0 || len == 0)
					return -1;
				for(i = 0; i < len; i++){
					if(c[i] == 0) return 1;
					if(buffer[i] != c[i]){
						l2 = getlen(c);
						if(l2 > len)
							return -1;
						return 1;
					}
				}
				if(c[i] != 0)
					return -1;
				return 0;
			}
			int index(const CharT c, int start = 0) const{
				if(buffer == 0 || len == 0)
					return -1;
				for(int i = start; i < len; i++){
					if(buffer[i] == c)
						return i;
				}
				return -1;
			}
			virtual int index(const CharT *s, const int start = 0) const{
				int i, j;
				if(len == 0 || s == 0)
					return -1;
				else if(s[0] == 0) return -1;
				for(i = start; i < len; i++){
					if(buffer[i] == s[0]){
						for(j = 0; buffer[i + j] != 0; j++){
							if(buffer[i + j] != s[j])
								continue;
						}
						return i;
					}
				}
				return -1;
			}
			inline int index(const BasicString<CharT> s) const{
				return index(s.buffer);
			}
			int rindex(const CharT c, int end = 0) const{
				if(len == 0) return -1;
				if(end == 0) end = len - 1;
				for(int i = end; i >= 0; i--){
					if(buffer[i] == c)
						return i;
				}
				return -1;
			}
			virtual int rindex(const CharT *s, int end = 0) const{
				int i, j, ssize, e;
				bool is_ok = true;
				if(len == 0 || s == 0) return -1;
				else{
				       	if(s[0] == 0) return -1;
				}
				ssize = getlen(s);
				if(end == 0)
					e = len - ssize;
				else{
					if(end > (len - ssize))
						return -1;
					else
						e = end;
				}
				for(i = e; i >= 0; i--){
					if(buffer[i] == s[0]){
						for(j = 0; j < ssize - 1; j++){
							if(charAt(i + j) != s[j]){
								is_ok = false;
								break;
							}
						}
						if(is_ok)
							return len - (i + j + 1);
					}
				}
				return -1;
			}
			inline int rindex(const BasicString<CharT> &s, int end = 0) const{
				return rindex(s.buffer, end);
			}
			inline bool startsWith(const CharT c) const{
				return (index(c) == 0)?true:false;
			}
			inline bool startsWith(const CharT *s) const{
				return (index(s) == 0)?true:false;
			}
			inline bool startsWith(const BasicString<CharT> &s) const{
				return (index(s.buffer) == 0)?true:false;
			}
			inline const bool endsWith(const CharT c){
				return (rindex(c) == 0)?true:false;
			}
			inline bool endsWith(const CharT *s) const{
				return (rindex(s) == 0)?true:false;
			}
			inline bool endsWith(const BasicString<CharT> &s) const{
				return (rindex(s.buffer) == 0)?true:false;
			}
			inline bool hasSubstring(const CharT *s) const{
				return (index(s) >= 0)?true:false;
			}
			inline bool hasSubstring(const BasicString<CharT> &s) const{
				return (index(s.buffer) >= 0)?true:false;
			}
		/** Returns a C char * representation of this String, please
		 *  do dot delete or free the memory used by this pointer,
		 *  this class's destructor will take care of the proper
		 *  memory cleanup.
		 *  \return A C char * equivalent to the data stored in this
		 *  object. */
			/*CharT *toCharPtr() const{
				return buffer;
			}*/
			inline const BasicString<CharT> &operator=(const CharT c){
				assign(c);
				return *this;
			}
			inline const BasicString<CharT> &operator=(const CharT *s){
				assign(s);
				return *this;
			}
			inline const BasicString<CharT> &operator+=(const CharT c){
				concat(c);
				return *this;
			}
			inline const BasicString<CharT> &operator+=(const CharT *s){
				concat(s);
				return *this;
			}
			inline const BasicString<CharT> &operator+=(const BasicString<CharT> &s){
				concat(s.buffer);
				return *this;
			}
			inline bool operator==(const CharT c) const{
				return equals(c);
			}
			inline bool operator==(const CharT *s) const{
				return equals(s);
			}
			inline bool operator==(const BasicString<CharT> &s) const{
				return equals(s);
			}
			inline const bool operator!=(const CharT c){
				return (equals(c))?false:true;
			}
			inline const bool operator!=(const CharT *s){
				return (equals(s))?false:true;
			}
			inline const bool operator!=(const BasicString<CharT> &s){
				return (equals(s))?false:true;
			}
			inline const void biteLeft(const int n){
				if(n >= len){
					delete[] buffer;
					buffer = new CharT[1];
					buffer[0] = 0;
					len = 0;
				}
				else{
					CharT *tmp;
					tmp = new CharT[len];
					copy(tmp, buffer, len - n, 0, n);
					delete[] buffer;
					buffer = tmp;
					len -= n;
				}
			}
	};

	class CharString:public BasicString<char>{
		public:
			CharString(){;}
			CharString(const char *s);
			CharString(const CharString &s);
			virtual const CharString &operator=(const char *s);
			virtual const CharString &operator=(const CharString &s);
			int index(const char *s, const int start = 0) const;
			int rindex(const char *s, const int end = 0) const;
			inline bool startsWith(const char *s) const{
				return (index(s, 0) == 0)?true:false;
			}
			inline bool startsWith(const CharString &s) const{
				return (index(s.buffer) == 0)?true:false;
			}
	};
};
#endif

