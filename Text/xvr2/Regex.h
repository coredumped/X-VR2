/*
 * $Id$
 */
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
#ifndef __XVR2_TEXT_REGEX_H__
#define __XVR2_TEXT_REGEX_H__
#include<xvr2/xvr2config.h>
#include<xvr2/String.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/Text/RegexException.h>

namespace xvr2{
	namespace Text {
		/** Use this class to handle and work with POSIX regular expressions.
		 *  This class makes exclusive use of the GNU regex library as provided
		 *  by GLIBC.
		 *  This class provides abstraction over the regex compilation process
		 *  since it is performed implicitly after you add a new pattern
		 *  expression.<br>
		 *  .  <br>
		 *  .  <br>
		 *  .  <br>
		 *  String str1 = "A long time ago in a galaxy far far away...";<br>
		 *  String str2 = "At some point in the future...";<br>
		 *  Regex r;<br>
		 *  r.pattern("ago");<br>
		 *  if(r.match(str1)) cout << "Pattern " << str1 << " matches" << endl;<br>
		 *  	cout << "Pattern " << str1 << " doesn't match" << endl;<br>
		 *  if(r.match(str2)) cout << "Pattern " << str2 << " matches" << endl;<br>
		 *  	cout << "Pattern " << str1 << " doesn't match" << endl;<br>
		 *  .  <br>
		 *  .  <br>
		 *  .  <br>*/
		class Regex:public xvr2::Object{
			private:
				void *handle;
				/** Tells wheter the pattern has already been compiled
				 *  by the regex engine */
				bool compiled;
				String *_pattern;
			protected:
				/** Holds the regex compilation flags */
				int cflags;
				/** Compiles the provided pattern. This method will
				 *  make use of the regcomp function call in order
				 *  to have a regex usable structure.
				 *  I for some reason the pattern object is null an
				 *  appropiate exception will be thrown.
				 *  \throws NullPointer if the regex pattern
				 *  has not been initialized yet
				 *  \throws RegexException if regex compilation or
				 *  matching fails at library level.
				 */
				virtual void compile();
			public:
				/** Default constructor, This one wont perform pattern
				 *  autocompilation and is required that the pattern 
				 *  gets defined and successfully compiled before any
				 *  match methods are applied to it. */
				Regex();
				/** When calling this construtor the provided pattern
				 *  will be instantly compiled and the use of any match
				 *  methods can be done inmediately. However you must
				 *  verify that the pattern compilation has succeded by
				 *  checking any of the exceptions that might by thrown.
				 *  \param pat Is the pattern to be compiled and match
				 *  against during the Regex::match method calls.
				 *  \throws Exception::Regex If regex compilation fails
				 *  at library level.  */
				Regex(const char *pat);
				/** When calling this construtor the provided pattern
				 *  will be instantly compiled and the use of any match
				 *  methods can be done inmediately. However you must
				 *  verify that the pattern compilation has succeded by
				 *  checking any of the exceptions that might by thrown.
				 *  \param pat Is the pattern to be compiled and match
				 *  against during the Regex::match method calls.
				 *  \throws Exception::Regex If regex compilation fails
				 *  at library level.  */
				Regex(const String &pat);
				~Regex();
				/** Returns of specifies the pattern to be used in
				 *  future Regex::match calls.
				 *  If the pattern is provided then it will be compiled
				 *  automagically, compilation will make use of previous
				 *  options like useExtended() and ignoreCase().
				 *  \param pat Is the regular expression pattern to be
				 *  used.
				 *  \return The pattern currently in use.
				 *  \throws Exception::NullPointer If the regex pattern
				 *  has not been initialized yet
				 *  \throws Exception::Regex If regex compilation fails
				 */
				const char *pattern(const char *pat = 0);
				/** If called before assigning a pattern the regex
				 *  compilation will add support for extended regular
				 *  expressions.
				 *  \param u If true then pattern compilation will use
				 *  extended regular exprenssions, otherwise common
				 *  posix regular expressions will be used. */
				void useExtended(bool u = true);
				/** If called before assigning a pattern the regex
				 *  compilation will will verify matches disregarding
				 *  the matchable string case (so it wont matter if it
				 *  is uppercase or lowercase).
				 *  \param u If true then pattern compilation will 
				 *  ignore case, otherwise the matching algorithms
				 *  will be case sensitive. */
				void ignoreCase(bool u = true);
				/** You may use this method as a shortcut when you need
				 *  to test pattern matching against a single pattern
				 *  once and dont want to create a Regex object.
				 *  The method internally creates a Regex object
				 *  compiles the given pattern and verifies if the
				 *  given string matches or not.
				 *  @param pattern Is the regular expression to be used
				 *  @param str The string to test for matches against
				 *  pattern.
				 *  @param case_sensitive Wheter pattern matching should should
				 *  be case-sensitive or not.
				 *  @return true if it str matches, false if not
				 *  @throws xvr2::NullPointer if the regex pattern
				 *  has not been initialized yet
				 *  @throws xvr2::RegexException if regex compilation or
				 *  matching fails at library level. */
				static bool match(const String &pattern, const String &str, bool case_sensitive = true);
				/** By using the compiled regex it attempts to check
				 *  if the provided string matches the previously 
				 *  given pattern.
				 *  \param str The string o test for matches against
				 *  the given pattern
				 *  \return true if it str matches, false if not */
				bool matches(const char *str);
				/** By using the compiled regex it attempts to check
				 *  if the provided string matches the previously 
				 *  given pattern.
				 *  \param str The string o test for matches against
				 *  the given pattern
				 *  \return true if it str matches, false if not */
				bool matches(const String &str);
		};
	};
};

#endif
