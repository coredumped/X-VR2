/* $Id$ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "ExtendedRegex.h"
#include<regex.h>

namespace xvr2{

	namespace Text {

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
