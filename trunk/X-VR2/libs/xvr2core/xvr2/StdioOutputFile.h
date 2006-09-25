#ifndef __XVR2_STDIO_OUTPUT_FILE_H__
#define __XVR2_STDIO_OUTPUT_FILE_H__
#include<xvr2/Buffer.h>
#include<xvr2/FileInterface.h>
#include<xvr2/StdioInterface.h>
#include<xvr2/String.h>
#include<cstdio>

namespace xvr2 {
	/** TODO: Document this class */
	class StdioOutputFile : public WriteableFile, public StdioInterface {
		public:
			StdioOutputFile();
			StdioOutputFile(const String &fname, bool for_append = false);
			StdioOutputFile(FILE *__f);
			void open(const String &path);
			void open(const String &path, bool for_append = false);
			void close();
			bool opened();
			virtual ~StdioOutputFile();
			
			virtual StdioOutputFile &operator << (const Buffer &b);
			virtual StdioOutputFile &operator << (const String &s);
			virtual StdioOutputFile &write(void *data, UInt32 size);
			virtual StdioOutputFile &write(const Buffer &data);
			virtual StdioOutputFile &write(const String &s);
			
			UInt32 size();
			UInt32 tell();
			StdioOutputFile &seek(UInt32 _pos);
			StdioOutputFile &seekEnd();
			StdioOutputFile &seekBegin();
			StdioOutputFile &seekStep(UInt32 _step);
			StdioOutputFile &flush();
			
			bool eof();
	};
};

#endif /*STDIOOUTPUTFILE_H_*/
