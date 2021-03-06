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
#include"config.h"
#include"StringBuffer.h"

namespace xvr2 {
	StringBuffer::StringBuffer(){
	}
	StringBuffer::StringBuffer(const String &s){
		buffer = s;
	}
	StringBuffer::StringBuffer(const StringBuffer &s){
		buffer = s.toString();
	}
	const char StringBuffer::operator[](int idx) const{
		return buffer.charAt(idx);
	}
	const char StringBuffer::operator[](int idx){
		return buffer.charAt(idx);
	}
	const char *StringBuffer::toCharPtr() const{
		return buffer.toCharPtr();
	}
	StringBuffer &StringBuffer::operator<<(const String &s) {
		buffer.concat(s);
		return *this;
	}
	std::string StringBuffer::toString() const {
		return std::string(buffer);
	}
	void StringBuffer::eat(char *data, int len){
		buffer.eat(data, len);
	}
}
