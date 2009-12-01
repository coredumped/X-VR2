/*
 * $Id$
 */
#include"config.h"
#include"StringBuffer.h"

namespace xvr2 {
	StringBuffer::StringBuffer(){
		//buffer = new String();
	}
	StringBuffer::StringBuffer(const String &s){
		//buffer = new String(s.toCharPtr());
		buffer = s;
	}
	StringBuffer::StringBuffer(const StringBuffer &s){
		//buffer = new String(s.toString().toCharPtr());
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
	const String &StringBuffer::toString() const {
		return buffer;
	}
	void StringBuffer::eat(char *data, int len){
		buffer.eat(data, len);
	}
};
