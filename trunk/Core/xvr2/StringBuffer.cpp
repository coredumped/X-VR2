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
		buffer = new String(s.toString());
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
	std::string StringBuffer::toString() const {
		return std::string(*buffer);
	}
	void StringBuffer::eat(char *data, int len){
		buffer->eat(data, len);
	}
};
