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
#ifndef __XVR2_RAW_OUTPUT_STREAM_H__
#define __XVR2_RAW_OUTPUT_STREAM_H__
#include<xvr2/StreamInterface.h>
#include<xvr2/RawStreamInterface.h>
#include<xvr2/SystemException.h>

namespace xvr2 {
	
	class RawOutputStream : public WriteableStream, public RawStreamInterface {
		public:
			RawOutputStream();
			virtual ~RawOutputStream();
			RawOutputStream(int __fd);
			RawOutputStream(const String &fname);
			void open(int __fd);
			void open(const String &fname);
			virtual void close();

			int fd();
			virtual RawOutputStream &write(void *data, UInt32 size);
			virtual void flush();
			FileSizeT size();
			bool eof();
			virtual bool ready(int timeout = 100);
	};
};
#endif

