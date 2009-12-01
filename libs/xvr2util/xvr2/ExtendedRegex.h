/* $Id$ */
#ifndef __XVR2_EXTENDED_REGEX_H__
#define __XVR2_EXTENDED_REGEX_H__

#include<xvr2/Regex.h>

namespace xvr2{

	namespace Util{

		class ExtendedRegex : public xvr2::Util::Regex{
			protected:
				virtual void compile();
			public:
				ExtendedRegex();
				ExtendedRegex(const String &pattern);
				static bool match(const String &pattern, const String &str, bool case_sensitive = true);
		};

	};
};

#endif
