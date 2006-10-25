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
#ifndef __XVR2_FILEINTERFACE_H__
#define __XVR2_FILEINTERFACE_H__

#include<xvr2/Object.h>
#include<xvr2/Buffer.h>
#include<xvr2/String.h>

namespace xvr2 {
	
	/** File interface class. */
	template<class fSize_t>
	class StreamInterface : public Object {
		private:
		protected:
			//fSize_t _fsize;
		public:
			StreamInterface(){
				//_fsize = 0;
			}
			virtual ~StreamInterface(){}
			virtual void open(const String &path) = 0;
			virtual void close() = 0;
			virtual bool opened() = 0;
			virtual fSize_t size() = 0;
			virtual fSize_t tell() = 0;
			virtual StreamInterface<fSize_t> &seek(fSize_t _pos) = 0;
			virtual StreamInterface<fSize_t> &seekEnd() = 0;
			virtual StreamInterface<fSize_t> &seekBegin() = 0;
			virtual StreamInterface<fSize_t> &seekStep(fSize_t _step) = 0;
			virtual StreamInterface<fSize_t> &flush() = 0;
			virtual bool eof() = 0;
	};
	
	/** To be used with files equal or smaller in size than 4Gb. */
	class StreamInterface4G : public virtual StreamInterface<UInt32> {
	};
	
	/** Implements readable/input files. */
	class ReadableStream : public virtual StreamInterface4G {
		public:
			virtual ReadableStream &operator >> (UInt32 n);
			virtual ReadableStream &operator >> (double n);
			virtual ReadableStream &operator >> (UInt64 n);
			UInt32 read(UInt32 n);
			UInt32 read(double n);
			UInt32 read(UInt64 n);
			virtual UInt32 read(void *data, UInt32 size) = 0;
			UInt32 read(Buffer &data, UInt32 size);
			/** Reads all data starting from the current position to the end of the
			 *  file and returns it in a Buffer object. */
			ReadableStream &read(Buffer &b);
			/** Loads the full contents and returns it in a Buffer */
			ReadableStream &readAll(Buffer &b);
	}; 
	
	/** Implements writeable/output files. */
	class WriteableStream : public virtual StreamInterface4G {
		public:
			virtual WriteableStream &operator << (const Buffer &b);
			virtual WriteableStream &operator << (const String &s);
			virtual WriteableStream &write(void *data, UInt32 size) = 0;
			virtual WriteableStream &write(const Buffer &data);
			virtual WriteableStream &write(const String &s);
	};
};

#endif
