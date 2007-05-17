/*
 * $Id$
 */
#ifndef __XVR2_PLATFORM_EXCEPTION_H__
#define __XVR2_PLATFORM_EXCEPTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>

namespace xvr2 {
	namespace Platform {
		/** Generic platform exception */
		class PlatformException:public Exception{
			public:
				/**
				 * Default constructor
				 */
				PlatformException();
				PlatformException(const String &error_message);
		};
	};
};

#endif
