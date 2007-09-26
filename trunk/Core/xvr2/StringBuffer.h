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
#ifndef __XVR2_STRING_BUFFER_H__
#define __XVR2_STRING_BUFFER_H__
#include<xvr2/String.h>
#define __XVR2_ENABLE_BASIC_STRING_BUFFER__
#include<xvr2/BasicStringBuffer.h>
namespace xvr2 {
	class StringBuffer : public BasicStringBuffer<String>{
		public:
			StringBuffer();
			StringBuffer(const StringBuffer &s);
			StringBuffer(const String &s);
			const char operator[](int idx) const;
			const char operator[](int idx);
			const char *toCharPtr() const;
			StringBuffer &operator<<(const String &s);
			virtual std::string toString() const;
			/** Will append to the String len characters from the data buffer */
			void eat(char *data, int len);
	};
}

#endif
