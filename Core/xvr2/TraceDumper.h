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
#ifndef __XVR2_EXCEPTION_TRACE_DUMPER_H__
#define __XVR2_EXCEPTION_TRACE_DUMPER_H__
#include<xvr2/Object.h>

namespace xvr2{
	class ExceptionTracer : public Object {
		private:
			static bool isEnabled();
		protected:
			virtual void dumpTrace();
		public:
			ExceptionTracer();
			static void enable();
			static void disable();
			const char *backtrace();
	};
}

#endif
