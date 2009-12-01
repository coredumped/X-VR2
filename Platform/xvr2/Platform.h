/* $Id$ */
/***************************************************************************
 *            Platform.h
 *
 *  Tue Sep 12 15:48:28 2006
 *  Copyright  2006  Juan V. Guerrero
 *  mindstorm2600 at users dot sourceforge dot net
 ****************************************************************************/

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
 
#ifndef __XVR2_PLATFORM_H__
#define __XVR2_PLATFORM_H__

#include<xvr2/String.h>
#include<xvr2/Platform/PlatformException.h>
#include<xvr2/Platform/CPU.h>
#include<vector>

#if defined(__linux) || defined(__linux__) || defined(linux__) || defined(__LINUX__) || defined(__LINUX) || defined(LINUX__)
#define XVR2_HOST_PLATFORM_LINUX
#else

#if defined(__sun) || defined(__sun__) || defined(sun__)
#define XVR2_HOST_PLATFORM_SOLARIS
#endif

#endif



namespace xvr2 {
	namespace Platform {
		/** Holds runtime information regarding the system we're running on. */
		struct SystemInformation : public xvr2::Object {
			/** Obtains how many CPUs the system has installed */
			static UInt32 cpuCount();
			/** Returns a list with the details of each CPU found */
			static const CPU &getCPU(UInt32 idx = 0);
		
			/** Gives the total amount of memory the system has which
			 *  is a sum of physical + swap. */
			static UInt64 memorySize();
			/** Returns the mount of physical memory installed. */
			static UInt64 physicalMemorySize();
			/** Returns the mount of swap memory installed. */
			static UInt64 swapSize();
		
			/** Returns the distribution name for the OS and distribution specific version. */
			static const String &OSDistribution();
			static const String &OSName();
			static const String &OSVersionString();
			static const std::vector<int> &OSVersion();
		};
	};
};


#endif /* _PLATFORM_H */
