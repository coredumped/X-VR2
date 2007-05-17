/* $Id$ */
#include "ExtendedRegex.h"
#include<regex.h>

namespace xvr2{

	namespace Util{

		ExtendedRegex::ExtendedRegex():Regex(){
			cflags |= REG_EXTENDED;
		}
		
		ExtendedRegex::ExtendedRegex(const String &pattern):Regex(pattern){
			cflags |= REG_EXTENDED;
		}

		void ExtendedRegex::compile(){
			cflags |= REG_EXTENDED;
			Regex::compile();
		}
		bool ExtendedRegex::match(const String &pattern, const String &str, bool case_sensitive){
			bool ret = false;
			try{
				ExtendedRegex r(pattern);
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
