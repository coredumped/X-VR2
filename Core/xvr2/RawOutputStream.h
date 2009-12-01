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
#ifndef __XVR2_RAW_OUTPUT_STREAM_H__
#define __XVR2_RAW_OUTPUT_STREAM_H__
#include<xvr2/StreamInterface.h>
#include<xvr2/RawStreamInterface.h>
#include<xvr2/SystemException.h>

namespace xvr2 {
/** @todo Document RawOutputStream class */
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
}
#endif

