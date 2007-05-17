/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/MessageStrings.h>
#include"PlatformException.h"

namespace xvr2 {
	namespace Platform {
		static const char *_excepPlatformException = "Unknown platform related exception.";
		PlatformException::PlatformException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_PlatformException);
#endif
			description = (char *)_excepPlatformException;
		}

		PlatformException::PlatformException(const String &error_message){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_PlatformException);
#endif
			description = (char *)error_message.toCharPtr();
		}
	};
};
