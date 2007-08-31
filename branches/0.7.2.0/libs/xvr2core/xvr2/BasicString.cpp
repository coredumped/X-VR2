/*
 * $Id$
 */
#define __XVR2_ENABLE_BASIC_STRING__
#include"config.h"
#include"BasicString.h"

namespace xvr2 {

	/////////////////////////////////////////////////////////
	// BasicString
	/////////////////////////////////////////////////////////
	/*BasicString::BasicString(){
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(BasicString);
#endif
	}

	int BasicString::index(const char *s){
		return std::string::find(s);
	}

	int BasicString::index(const char *s) const {
		return std::string::find(s);
	}

	int BasicString::index(const BasicString &s){
		return std::string::find(s.c_str());
	}

	int BasicString::rindex(const char *s) const{
		return std::string::find_last_of(s);
	}

	int BasicString::rindex(const char *s){
		return std::string::find_last_of(s);
	}

	int BasicString::rindex(const BasicString &s){
		return std::string::find_last_of(s.c_str());
	}
	
	BasicString &BasicString::biteLeft(int howmany){
		std::string::erase(begin(), begin() + howmany);
		return *this;
	}

	BasicString &BasicString::biteRight(int howmany){
		//std::string::erase(std::string::size() - 1);
		std::string::erase(end() - howmany, end());
		return *this;
	}

	BasicString &BasicString::trimLeft(const char c){
		while(size() > 0 && at(0) == c){
			std::string::erase(0);
		}
		return *this;
	}

	BasicString &BasicString::trimRight(const char c){
		while(size() > 0 && at(size() - 1) == c){
			std::string::erase(size() - 1);
		}
		return *this;
	}
	bool BasicString::equals(const char *s){
		return (std::string::compare(s) == 0)?true:false;
	}
	bool BasicString::operator==(const char *s){
		return (std::string::compare(s) == 0)?true:false;
	}


	/////////////////////////////////////////////////////////
	// BasicWString
	/////////////////////////////////////////////////////////
	/*BasicWString::BasicWString(){

#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(BasicWString);
#endif
	}

	int BasicWString::index(const wchar_t *s){
		return std::wstring::find(s);
	}

	int BasicWString::index(const wchar_t *s) const {
		return std::wstring::find(s);
	}

	int BasicWString::index(const BasicWString &s){
		return std::wstring::find(s.c_str());
	}

	int BasicWString::rindex(const wchar_t *s) const{
		return std::wstring::find_last_of(s);
	}

	int BasicWString::rindex(const wchar_t *s){
		return std::wstring::find_last_of(s);
	}

	int BasicWString::rindex(const BasicWString &s){
		return std::wstring::find_last_of(s.c_str());
	}
	
	BasicWString &BasicWString::biteLeft(int howmany){
		std::wstring::erase(begin(), begin() + howmany);
		return *this;
	}

	BasicWString &BasicWString::biteRight(int howmany){
		std::wstring::erase(end() - howmany, end());
		return *this;
	}

	BasicWString &BasicWString::trimLeft(const wchar_t c){
		while(at(0) == c){
			std::wstring::erase(0);
		}
		return *this;
	}

	BasicWString &BasicWString::trimRight(const wchar_t c){
		while(at(size() - 1) == c){
			std::wstring::erase(size() - 1);
		}
		return *this;
	}*/
};
