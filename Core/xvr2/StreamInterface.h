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
#ifndef __XVR2_FILEINTERFACE_H__
#define __XVR2_FILEINTERFACE_H__

#include<xvr2/Object.h>
#include<xvr2/Buffer.h>
#include<xvr2/String.h>
#include<xvr2/StreamException.h>

namespace xvr2 {
	
	/** @brief File interface class.
	 *  @todo Document all classes in StreamInterface.h */
	class StreamInterface : public Object {
		private:
		protected:
		public:
			StreamInterface();
			virtual ~StreamInterface();
			virtual void open(const String &path) = 0;
			virtual void close() = 0;
			virtual bool opened() = 0;
			virtual FileSizeT size() = 0;
			virtual FileOffsetT tell() = 0;
			virtual void seek(FileOffsetT _pos) = 0;
			virtual void seekEnd() = 0;
			virtual void seekBegin() = 0;
			virtual void seekStep(FileOffsetT _step) = 0;
			virtual void flush() = 0;
			virtual bool eof() = 0;
	};
	
	/** Implements readable/input streams.
	 *  Considerations
	 *  1. Readable streams ARE NOT flushable, that is since they are
	 *     considered input devices there is no input to push down the
	 *     pipe.
	 *  2. When subclassing sometimes is enough to just implement the
	 *     UInt32 ReadableStream::read(void *data, UInt32 size) method.
	 *  3. Also you must provide an open method which takes a String as
	 *     a parameter which specifies the stream "address", that address
	 *     can be a filesystem path or any other address which your
	 *     implmentation is meant to handle. */
	class ReadableStream : public virtual StreamInterface {
		protected:
			bool handles_timeouts;
			int timeout_msecs;
		public:
			ReadableStream(){
				handles_timeouts = false;
				timeout_msecs = 0;
			}
			virtual ReadableStream &operator >> (UInt32 n);
			virtual ReadableStream &operator >> (double n);
			virtual ReadableStream &operator >> (UInt64 n);
			UInt32 read(UInt32 n);
			UInt32 read(double n);
			UInt32 read(UInt64 n);
			virtual UInt32 read(void *data, UInt32 size) = 0;
			virtual UInt32 read(Buffer &data, UInt32 size);
			/** Reads all data starting from the current position to the end of the
			 *  file and returns it in a Buffer object. */
			virtual ReadableStream &read(Buffer &b);
			/** Loads the full contents and returns it in a Buffer */
			virtual ReadableStream &readAll(Buffer &b);
			virtual void flush();
			virtual void setTimeout(int millisecs){
				timeout_msecs = millisecs;
			}
	}; 
	
	/** Implements writeable/output files. */
	class WriteableStream : public virtual StreamInterface {
		public:
			virtual WriteableStream &operator << (const Buffer &b);
			virtual WriteableStream &operator << (const String &s);
			virtual WriteableStream &write(void *data, UInt32 size) = 0;
			virtual WriteableStream &write(const Buffer &data);
			virtual WriteableStream &write(const String &s);
			virtual void seek(FileOffsetT _pos);
			virtual void seekEnd();
			virtual void seekBegin();
			virtual void seekStep(FileOffsetT _step);
	};

	//class RandomAccessStream : public virtual StreamInterface {
	//};
}

#endif

