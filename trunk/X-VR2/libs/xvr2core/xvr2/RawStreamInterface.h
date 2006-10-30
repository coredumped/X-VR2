/* $Id$ */
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
			virtual bool ready() = 0;
	};
};

#endif

