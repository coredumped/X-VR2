/*
 * $Id$
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
			const StringBuffer &operator<<(const String &s) const;
			const String &toString() const;
	};
};

#endif
