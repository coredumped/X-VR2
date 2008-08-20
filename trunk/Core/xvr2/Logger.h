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

#ifndef __XVR2_LOGGER_H__
#define __XVR2_LOGGER_H__
#include<xvr2/String.h>
#include<xvr2/StringBuffer.h>

namespace xvr2 {

	class Logger : public xvr2::Object {
		private:
		protected:
			virtual void write() = 0;
			virtual void append(const xvr2::String &s) = 0;
			Logger();
		public:
			virtual ~Logger();
			virtual Logger &operator << (const String &s);
			virtual Logger &operator << (const StringBuffer &s);
			virtual Logger &operator << (Logger &l);
			virtual Logger &operator << (Object &s);
	};

}

#endif
