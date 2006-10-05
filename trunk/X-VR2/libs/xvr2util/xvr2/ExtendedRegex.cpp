#include "ExtendedRegex.h"

namespace xvr2{

	namespace Util{

		ExtendedRegex::ExtendedRegex():Regex(){
			useExtended();
		}
		
		ExtendedRegex::ExtendedRegex(const String &pattern):Regex(pattern){
			useExtended();
		}

		void ExtendedRegex::compile(){
			useExtended();
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
		/*ExtendedRegex::~ExtendedRegex()
		{
		}*/

	};

};
