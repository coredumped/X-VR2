/* $Id$ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
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
#else
typedef long int		FileSizeT;
typedef long int		FileOffsetT;
#endif

#endif
