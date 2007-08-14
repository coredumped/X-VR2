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
#if defined(USING_LINUX) || defined(USING_SOLARIS)
#include<sys/types.h>
typedef off_t			FileSizeT;
typedef off_t			FileOffsetT;
typedef int			OSErrorCodeT;
#else
typedef long int		FileSizeT;
typedef long int		FileOffsetT;
typedef int			OSErrorCodeT;
#endif

#endif
