/*
 * $Id$
 *
 * 
 */
#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include<xvr2/xvr2config.h>
#ifdef _STDINT_H
typedef uint8_t			UInt8;
typedef int8_t			Int8;
typedef uint16_t	  	UInt16;
typedef int16_t			Int16;
typedef uint32_t		UInt32;
typedef int32_t			Int32;
typedef uint64_t		UInt64;
typedef int64_t			Int64;
#else
typedef unsigned char		UInt8;
typedef signed char		Int8;
typedef unsigned short  	UInt16;
typedef signed short    	Int16;
typedef unsigned int    	UInt32;
typedef signed int      	Int32;
typedef unsigned long long	UInt64;
typedef long long		Int64;
#endif

#endif
