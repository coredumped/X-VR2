/*
 * $Id$
 */
#include<regex.h>
#include"config.h"
#include<xvr2/Regex.h>
#ifdef USE_EMBEDDED_CLASSNAMES
#include<xvr2/_xvr2utilClassNames.h>
#endif

namespace xvr2 {
	namespace Util {
		Regex::Regex(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_Regex);
#endif
			compiled = false;
			cflags = 0;
			_pattern = 0;
			handle = 0;
		}

		Regex::Regex(const char *pat){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_Regex);
#endif
			compiled = false;
			cflags = 0;
			_pattern = 0;
			handle = 0;
			pattern(pat);
		}

		Regex::Regex(const String &pat){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_Regex);
#endif
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
				r = (regex_t *)handle;
			}
			if(_pattern == 0)
				throw NullPointer();
			ret = regcomp(r, _pattern->toCharPtr(), cflags);
			if(ret != 0){
				throw RegexException(ret);
			}
			compiled = true;
		}

		void Regex::useExtended(bool u){
			if(u)
				cflags |= REG_EXTENDED;
			else
				cflags &= REG_EXTENDED;
			if(compiled && handle != 0){
				//Recompile again
				regex_t *r;
				r = (regex_t *)handle;
				regfree(r);
				handle = 0;
				delete r;
				compile();
			}
		}

		void Regex::ignoreCase(bool u){
			if(u)
				cflags |= REG_ICASE;
			else
				cflags &= REG_ICASE;
			if(compiled){
				//Recompile again
				regex_t *r;
				r = (regex_t *)handle;
				regfree(r);
				handle = 0;
				delete r;
				compile();
			}
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

		/*bool Regex::match(const char *pat, const char *str){
			bool ret = false;
			try{
				Regex r(pat);
				ret = r.matches(str);
			}
			catch(...){
				throw;
			}
			return ret;
		}*/

		bool Regex::match(const String &pat, const String &str, bool case_sensitive){
			bool ret = false;
			try{
				Regex r(pat);
				if(!case_sensitive){
					 r.ignoreCase();
				}
				ret = r.matches(str);
			}
			catch(...){
				throw;
			}
			return ret;
		}
	};
};
