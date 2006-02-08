/*
 * $Id$
 */
#ifndef __XVR2_DEBUG_CONSOLE_H__
#define __XVR2_DEBUG_CONSOLE_H__
#include<xvr2/Object.h>
#include<xvr2/Console.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {
	class DebugConsole : protected Console {
		public:
			DebugConsole();
			void setOutput(TextOutput *to = 0);
			const DebugConsole &operator<<(const String &s) const;
	};

	/** Standard X-VR2 debug console */
	extern DebugConsole debugConsole;
};
#endif
