/* $Id$ */
#ifndef __XVR2_FILEINTERFACE_H__
#define __XVR2_FILEINTERFACE_H__

#include<xvr2/Object.h>
#include<xvr2/File.h>

namespace xvr2 {
	
	/** File interface class. */
	template<class fSize_t>
	class FileInterface : public Object {
		private:
		protected:
			fSize_t _fsize;
		public:
			FileInterface(){
				_fsize = 0;
			}
			virtual ~FileInterface(){}
			virtual void open(const String &path) = 0;
			virtual void close() = 0;
			virtual bool opened() = 0;
			virtual fSize_t size() = 0;
			virtual fSize_t tell() = 0;
			virtual FileInterface<fSize_t> &seek(fSize_t _pos) = 0;
			virtual FileInterface<fSize_t> &seekEnd() = 0;
			virtual FileInterface<fSize_t> &seekBegin() = 0;
			virtual FileInterface<fSize_t> &seekStep(fSize_t _step) = 0;
			virtual FileInterface<fSize_t> &flush() = 0;
	};
	
	/** To be used with files equal or smaller in size than 4Gb. */
	class FileInterface4G : public FileInterface<UInt32> {
	};
	
	/** Implements readable/input files. */
	class ReadableFile : public FileInterface4G {
		public:
			virtual ReadableFile &operator >> (UInt32 n);
			virtual ReadableFile &operator >> (double n);
			virtual ReadableFile &operator >> (UInt64 n);
			virtual UInt32 read(UInt32 n);
			virtual UInt32 read(double n);
			virtual UInt32 read(UInt64 n);
			virtual UInt32 read(void *data, UInt32 size) = 0;
			virtual UInt32 read(Buffer &data, UInt32 size);
			/** Reads all data starting from the current position to the end of the
			 *  file and returns it in a Buffer object. */
			virtual ReadableFile &read(Buffer &b);
			/** Loads the full contents and returns it in a Buffer */
			virtual ReadableFile &readAll(Buffer &b);
	}; 
	
	/** Implements writeable/output files. */
	class WriteableFile : public FileInterface4G {
		public:
			virtual WriteableFile &operator << (const Buffer &b);
			virtual WriteableFile &operator << (const String &s);
			virtual WriteableFile &write(void *data, UInt32 size) = 0;
			virtual WriteableFile &write(const Buffer &data);
			virtual WriteableFile &write(const String &s);
	};
};

#endif
