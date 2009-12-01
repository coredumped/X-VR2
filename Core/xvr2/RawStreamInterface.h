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
#ifndef __XVR2_RAW_STREAM_INTERFACE_H__
#define __XVR2_RAW_STREAM_INTERFACE_H__
#include<xvr2/StreamInterface.h>

namespace xvr2 {
	class RawStreamInterface : public virtual StreamInterface {
		protected:
			int _fd;
			bool _a_close;
			bool _is_opened;
			RawStreamInterface(){};
		public:
			virtual FileSizeT size();
			virtual FileOffsetT tell();
			virtual bool opened();
			virtual bool ready(int t = 100) = 0;
	};
}

#endif

