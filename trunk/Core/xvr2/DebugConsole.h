/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_DEBUG_CONSOLE_H__
#define __XVR2_DEBUG_CONSOLE_H__
#include<xvr2/Object.h>
#include<xvr2/Console.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {
	class DebugConsole : protected Console {
		protected:
			bool _enabled;
		public:
			DebugConsole();
			void setOutput(TextOutput *to = 0);
			const DebugConsole &operator<<(const String &s) const;
			void enable();
			void disable();
			bool enabled();
	};

	/** Standard X-VR2 debug console */
	extern DebugConsole debugConsole;
};
#endif
