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
#ifndef __XVR2_RAW_INPUT_STREAM_H__
#define __XVR2_RAW_INPUT_STREAM_H__
#include<xvr2/StreamInterface.h>
#include<xvr2/RawStreamInterface.h>
#include<xvr2/SystemException.h>
#include<cerrno>

namespace xvr2 {

	/** TODO: Document this class */
	class RawInputStream : public ReadableStream, public RawStreamInterface {
		private:
			bool reached_eof;
		public:
			RawInputStream();
			virtual ~RawInputStream();
			RawInputStream(int __fd);
			RawInputStream(const String &fname);
			void open(int __fd);
			void open(const String &fname);
			virtual void close();

			virtual UInt32 read(void *data, UInt32 size);
			int fd();
			bool eof();
			virtual void seek(FileOffsetT _pos);
			virtual void seekEnd();
			virtual void seekBegin();
			virtual void seekStep(FileOffsetT _step);
			virtual bool ready(int timeout = 100);
	};

	class RawInputStreamTimeoutException : public StreamException {
		protected:
			int _fd;
			int _msecs;
		public:
			RawInputStreamTimeoutException(int __fd);
			RawInputStreamTimeoutException(int __fd, int __msecs);
			int fd();
			int millis();
	};
};

#endif

