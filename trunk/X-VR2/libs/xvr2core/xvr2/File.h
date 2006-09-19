#ifndef __XVR2_FILE_H__
#define __XVR2_FILE_H__
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/Buffer.h>
#include<fstream>

//TODO: Document me

namespace xvr2{
		
	enum FileOpenMode{
		/** The file can only be read secuentially */
		READ_ONLY = 1,
		/** The file can only be writen secuentially */
		WRITE_ONLY = 2,
		/** The file can be read-written,
		 *  be carefull if your writing data
		 *  to an already existing file*/
		READ_WRITE = 3,
		/** The file is open for writing
		 *  at the end */
		APPEND = 4
	};
	
	class File : public xvr2::Object, protected std::fstream {
		private:
		protected:
			UInt32 _fsize;
		public:
			File();
			File(const String &path, const FileOpenMode mode = READ_WRITE);
			virtual ~File();
			virtual void open(const FileOpenMode mode);
			virtual void open(const String &path, const FileOpenMode mode);
			virtual void close();
			virtual const File &operator << (const Buffer &data);
			virtual const File &operator << (const String &data);
			virtual const File &write(const Buffer &data);
			virtual const File &write(const String &data);
			virtual File &operator >> (UInt32 n);
			virtual File &operator >> (double n);
			virtual File &operator >> (UInt64 n);
			virtual UInt32 read(UInt32 n);
			virtual UInt32 read(double n);
			virtual UInt32 read(UInt64 n);
			virtual UInt32 read(void *data, int size);
			virtual UInt32 read(Buffer &data, int size);
			/** Reads all data starting from the current position to the end of the
			 *  file and returns it in a Buffer object. */
			virtual Buffer &read();
			/** Loads the full contents and returns it in a Buffer */
			virtual Buffer &readAll();
			virtual bool opened();
			virtual UInt32 size();
			virtual UInt32 tell();
			virtual File &seek(UInt32 _pos);
			virtual File &seekEnd();
			virtual File &seekBegin();
			virtual File &seekStep(UInt32 _step);
			virtual File &flush();
	};
};

#endif /*__XVR2_FILE_H__*/
