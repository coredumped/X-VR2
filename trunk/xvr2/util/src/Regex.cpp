/*
 * $Id$
 */
#include<regex.h>
#include<xvr2/Regex.h>

namespace xvr2 {
	namespace Util {
		Regex::Regex(){
			compiled = false;
			cflags = 0;
			_pattern = 0;
			handle = 0;
		}

		Regex::Regex(const char *pat){
			compiled = false;
			cflags = 0;
			_pattern = 0;
			handle = 0;
			pattern(pat);
		}

		Regex::Regex(const String &pat){
			compiled = false;
			cflags = 0;
			_pattern = 0;
			handle = 0;
			pattern(pat.toCharPtr());
		}

		const char *Regex::pattern(const char *p){
			if(p == 0)
				return _pattern->toCharPtr();
			xvr2_delete(_pattern);
			_pattern = new String(p);
			try{
				compile();
			}
			catch(...){
				throw;
			}
			return _pattern->toCharPtr();
		}

		void Regex::compile(){
			regex_t *r;
			int ret;
			if(handle == 0){
				r = new regex_t;
				handle = (void *)r;
			}
			else{
				r = (regex_t *)r;
			}
			if(_pattern == 0)
				throw Exception::NullPointer();
			ret = regcomp(r, _pattern->toCharPtr(), cflags);
			if(ret != 0){
				throw xvr2::Exception::Regex(ret);
			}
			compiled = true;
		}

		void Regex::useExtended(bool u){
			if(u)
				cflags |= REG_EXTENDED;
			else
				cflags &= REG_EXTENDED;
		}

		void Regex::ignoreCase(bool u){
			if(u)
				cflags |= REG_ICASE;
			else
				cflags &= REG_ICASE;
		}

		Regex::~Regex(){
			regex_t *r;
			r = (regex_t *)handle;
			if(compiled){
				regfree(r);
			}
			xvr2_delete(r);
			xvr2_delete(_pattern);
		}

		bool Regex::matches(const char *str){
			regex_t *r;
			int ret;
			try{
				if(handle == 0)
					compile();
			}
			catch(...){
				throw;
			}
			r = (regex_t *)handle;
			ret = regexec(r, str, 0, 0, 0);
			if(ret == 0)
				return true;
			return false;
		}

		bool Regex::matches(const String &str){
			regex_t *r;
			int ret;
			try{
				if(handle == 0)
					compile();
			}
			catch(...){
				throw;
			}
			r = (regex_t *)handle;
			ret = regexec(r, str.toCharPtr(), 0, 0, 0);
			if(ret == 0)
				return true;
			return false;
		}

		bool Regex::match(const char *pat, const char *str){
			bool ret = false;
			try{
				Regex r(pat);
				ret = r.matches(str);
			}
			catch(...){
				throw;
			}
			return ret;
		}

		bool Regex::match(const String &pat, const String &str){
			bool ret = false;
			try{
				Regex r(pat);
				ret = r.matches(str);
			}
			catch(...){
				throw;
			}
			return ret;
		}
	};
};
