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
#include<xvr2/ArrayIndexOutOfLimitsException.h>
#if __GNUC__ < 3
#include<string.h>
#else
#include<string>
#endif

namespace xvr2 {
	class BasicString : public Object, public std::string {
		protected:
			BasicString();
		public:
			~BasicString(){}
			virtual int index(const char *s);
			virtual int index(const char *s) const;
			virtual int index(const BasicString &s);
			virtual int rindex(const char *s);
			virtual int rindex(const char *s) const;
			virtual int rindex(const BasicString &s);
			virtual BasicString &biteLeft(int howmany = 1);
			virtual BasicString &biteRight(int howmany = 1);
			virtual BasicString &trimLeft(const char c = ' ');
			virtual BasicString &trimRight(const char c = ' ');
			virtual bool equals(const char *s);
			virtual bool operator==(const char *s);
	};
	class BasicWString : public Object, public std::wstring {
		protected:
			BasicWString();
		public:
			~BasicWString(){}
			virtual int index(const wchar_t *s);
			virtual int index(const wchar_t *s) const;
			virtual int index(const BasicWString &s);
			virtual int rindex(const wchar_t *s);
			virtual int rindex(const wchar_t *s) const;
			virtual int rindex(const BasicWString &s);
			virtual BasicWString &biteLeft(int howmany = 1);
			virtual BasicWString &biteRight(int howmany = 1);
			virtual BasicWString &trimLeft(const wchar_t c = ' ');
			virtual BasicWString &trimRight(const wchar_t c = ' ');
	};
};
#endif
