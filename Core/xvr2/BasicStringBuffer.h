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
#ifndef __XVR2_BASIC_STRING_BUFFER_H__
#define __XVR2_BASIC_STRING_BUFFER_H__
#ifndef __XVR2_ENABLE_BASIC_STRING_BUFFER__
#error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif
#include<xvr2/Object.h>
namespace xvr2 {
	template<class StringT>
	class BasicStringBuffer:public Object {
		public:
			typedef BasicStringBuffer<StringT> MySBType;
		protected:
			StringT buffer;
		public:

			BasicStringBuffer(){
			}
			~BasicStringBuffer(){
			}
			BasicStringBuffer(const StringT &s){
				buffer = s;
			}
			void clear(){
				buffer.clear();
			}
			virtual MySBType &operator<<(const StringT &s) {
				buffer.append(s);
				return *this;
			}
	};
}

#endif
