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

