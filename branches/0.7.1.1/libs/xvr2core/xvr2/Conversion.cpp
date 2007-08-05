/*
 * $Id$
 */
#include"config.h"
#include"Conversion.h"
#include"String.h"
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#if __GNUC__ < 3
#include<cstdlib.h>
#else
#include<cstdlib>
#endif
#ifdef HAVE_STRTOD
#define xvr2_strtod strtod
#endif
#ifdef HAVE_STRTOL
#define xvr2_strtol strtol
#endif
#ifdef HAVE_STRTOLL
#define xvr2_strtoll strtoll
#endif
#ifdef HAVE_STRTOUL
#define xvr2_strtoul strtoul
#endif
#ifdef HAVE_STRTOULL
#define xvr2_strtoull strtoull
#endif
#ifdef HAVE_STRTOF
#define xvr2_strtof strtof
#else
#ifdef HAVE_STRTOD
#define xvr2_strtof strtod
#endif
#endif
#ifdef HAVE_STRTOD
#define xvr2_strtod strtod
#endif
#ifdef HAVE_STRTOLD
#define xvr2_strtold strtold
#endif

namespace xvr2 {

	const Int32 String2Int32(const String &s, int base){
		Int32 val;
		char *errbuf;
		val = (Int32)xvr2_strtol(s.toCharPtr(), &errbuf, base);
		//Error chceking goes here.
		if(errbuf[0] != '\0'){
			throw NumberException();
		}
		return val;
	}
	const Int64 String2Int64(const String &s, int base){
		Int64 val;
		char *errbuf;
#if __WORDSIZE == 64
		val = (Int64)xvr2_strtol(s.toCharPtr(), &errbuf, base);
#else
		val = (Int64)xvr2_strtoll(s.toCharPtr(), &errbuf, base);
#endif
		if(errbuf[0] != '\0'){
			throw NumberException();
		}
		return val;
	}
	const UInt32 String2UInt32(const String &s, int base){
		UInt32 val;
		char *errbuf;
		val = (UInt32)xvr2_strtoul(s.toCharPtr(), &errbuf, base);
		//Error chceking goes here.
		if(errbuf[0] != '\0'){
			throw NumberException();
		}
		return val;
	}
	const UInt64 String2UInt64(const String &s, int base){
		UInt64 val;
		char *errbuf;
#if __WORDSIZE == 64
		val = (UInt64)xvr2_strtoul(s.toCharPtr(), &errbuf, base);
#else
		val = (UInt64)xvr2_strtoull(s.toCharPtr(), &errbuf, base);
#endif
		if(errbuf[0] != '\0'){
			throw NumberException();
		}
		return val;
	}
	const float String2float(const String &s){
		float val;
		char *errbuf;
		val = (float)xvr2_strtof(s.toCharPtr(), &errbuf);
		if(errbuf[0] != '\0'){
			throw NumberException();
		}
		return val;
	}
	const double String2double(const String &s){
		double val;
		char *errbuf;
		val = xvr2_strtod(s.toCharPtr(), &errbuf);
		if(errbuf[0] != '\0'){
			throw NumberException();
		}
		return val;
	}
	const long double String2longdouble(const String &s){
		long double val;
		char *errbuf;
		val = xvr2_strtold(s.toCharPtr(), &errbuf);
		if(errbuf[0] != '\0'){
			throw NumberException();
		}
		return val;
	}

	//Numeric to string conversions
};
