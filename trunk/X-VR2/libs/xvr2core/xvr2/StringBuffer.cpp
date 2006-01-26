/*
 * $Id$
 */
#include"config.h"
#include"StringBuffer.h"

namespace xvr2 {
	StringBuffer::StringBuffer(){
		buffer = new String();
	}
	StringBuffer::StringBuffer(const String &s){
		buffer = new String(s.toCharPtr());
	}
	StringBuffer::StringBuffer(const StringBuffer &s){
		buffer = new String(s.toString().toCharPtr());
	}
	const char StringBuffer::operator[](int idx) const{
		return buffer->charAt(idx);
	}
	const char StringBuffer::operator[](int idx){
		return buffer->charAt(idx);
	}
	const char *StringBuffer::toCharPtr() const{
		return buffer->toCharPtr();
	}
	const StringBuffer &StringBuffer::operator<<(const String &s) const {
		buffer->concat(s.toCharPtr());
		return *this;
	}
	const String &StringBuffer::toString() const {
		return *buffer;
	}
};
