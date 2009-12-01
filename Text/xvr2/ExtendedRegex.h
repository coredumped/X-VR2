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
#ifndef __XVR2_EXTENDED_REGEX_H__
#define __XVR2_EXTENDED_REGEX_H__

#include<xvr2/Text/Regex.h>

namespace xvr2 {

	namespace Text {

		class ExtendedRegex : public xvr2::Text::Regex{
			protected:
				virtual void compile();
			public:
				ExtendedRegex();
				ExtendedRegex(const String &pattern);
				/** @brief Verifies that a given string matches a specified paramter.
				 *  This method makes use of extended regular expressions to 
				 *  achieve its goals.
				 *  @param pattern The regex to be used for verifying matches
				 *  @param str The string to be matched against the pattern
				 *  @param case_sensitive If true then the pattern matching will
				 *  be case sensitive, if false, then it will be case insensitive.
				 *  @return true If the given string matches the patter, false
				 *  otherwise. */ 
				static bool match(const String &pattern, const String &str, bool case_sensitive = true);
		};

	};
};

#endif
