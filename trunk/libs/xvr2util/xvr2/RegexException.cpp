/*
 * $Id$
 */
#include<xvr2/xvr2config.h>
#include<_xvr2utilClassNames.h>
#include<xvr2/RegexException.h>
#include<xvr2/MessageStrings.h>
#include<regex.h>

namespace xvr2 {
	namespace Util {

		static const char *excepRegex = "Generic Regex exception";
		static const char *__rexp_REG_BADRPT = "Invalid  use  of  repetition  operators such as using ‘*’ as the first character.";
		static const char *__rexp_REG_BADBR = "Invalid use of back reference operator.";
		static const char *__rexp_REG_EBRACE = "Un-matched brace interval operators.";
		static const char *__rexp_REG_EBRACK = "Un-matched bracket list operators.";
		static const char *__rexp_REG_ERANGE = "Invalid use of the range operator, eg. the ending point  of  the range occurs prior to the starting point.";
		static const char *__rexp_REG_ECTYPE = "Unknown character class name.";
		static const char *__rexp_REG_ECOLLATE = "Invalid collating element.";
		static const char *__rexp_REG_EPAREN = "Un-matched parenthesis group operators.";
		static const char *__rexp_REG_ESUBREG = "Invalid back reference to a subexpression.";
		static const char *__rexp_REG_EEND = "Non specific error.  This is not defined by POSIX.2.";
		static const char *__rexp_REG_EESCAPE = "Trailing backslash.";
		static const char *__rexp_REG_BADPAT = "Invalid use of pattern operators such as group or list.";
		static const char *__rexp_REG_ESIZE = "Compiled  regular  expression  requires  a pattern buffer larger than 64Kb.  This is not defined by POSIX.2.";
		static const char *__rexp_REG_ESPACE = "The regex routines ran out of memory.";

		RegexException::RegexException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_RegexException);
#endif
			description = (char *)excepRegex;
		}




		RegexException::RegexException(int errx){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)_xvr2RegexException);
#endif
			switch(errx){
				case REG_BADRPT:
					description = (char *)__rexp_REG_BADRPT;
					break;
				case REG_BADBR:
					description = (char *)__rexp_REG_BADBR;
					break;
				case REG_EBRACE:
					description = (char *)__rexp_REG_EBRACE;
					break;
				case REG_EBRACK:
					description = (char *)__rexp_REG_EBRACK;
					break;
				case REG_ERANGE:
					description = (char *)__rexp_REG_ERANGE;
					break;
				case REG_ECTYPE:
					description = (char *)__rexp_REG_ECTYPE;
					break;
				case REG_ECOLLATE:
					description = (char *)__rexp_REG_ECOLLATE;
					break;
				case REG_EPAREN:
					description = (char *)__rexp_REG_EPAREN;
					break;
				case REG_ESUBREG:
					description = (char *)__rexp_REG_ESUBREG;
					break;
#ifdef USING_LINUX 
				case REG_EEND:
					description = (char *)__rexp_REG_EEND;
					break;
#endif
				case REG_EESCAPE:
					description = (char *)__rexp_REG_EESCAPE;
					break;
				case REG_BADPAT:
					description = (char *)__rexp_REG_BADPAT;
					break;
#ifdef USING_LINUX 
				case REG_ESIZE:
					description = (char *)__rexp_REG_ESIZE;
					break;
#endif
				case REG_ESPACE:
					description = (char *)__rexp_REG_ESPACE;
					break;
				default:
					description = (char *)excepRegex;
			}
		}
	};
};
