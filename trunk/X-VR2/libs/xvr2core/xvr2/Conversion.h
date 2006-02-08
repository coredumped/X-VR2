/*
 * $Id$
 */
#ifndef __XVR2_CONVERSION_H__
#define __XVR2_CONVERSION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/Object.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {

	//String to numeric conversions
	class String;
	/** Converts the given string s into an Int32 value */
	const Int32 String2Int32(const String &s, int base = 10);
	/** Converts the given string s into an Int64 value */
	const Int64 String2Int64(const String &s, int base = 10);
	/** Converts the given string s into an UInt32 value */
	const UInt32 String2UInt32(const String &s, int base = 10);
	/** Converts the given string s into an UInt64 value */
	const UInt64 String2UInt64(const String &s, int base = 10);
	/** Converts the given string s into a float value */
	const float String2float(const String &s);
	/** Converts the given string s into a double value */
	const double String2double(const String &s);
	/** Converts the given string s into a long double value */
	const long double String2longdouble(const String &s);

	//Numeric to string conversions
};

#endif
