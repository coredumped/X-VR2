/* $Id$ */
#ifndef __XVR2_STDIOINPUTFILE_H__
#define __XVR2_STDIOINPUTFILE_H__

#include<xvr2/StreamInterface.h>
#include<xvr2/StdioInterface.h>
#include<xvr2/String.h>
#include<cstdio>

namespace xvr2 {

	class StdioInputFile : public ReadableStream, private StdioInterface {
		public:
			StdioInputFile();
			StdioInputFile(const String &fname);
			StdioInputFile(FILE *__f);
			void open(const String &path);
			void close();
			bool opened();
			virtual ~StdioInputFile();
			UInt32 read(void *data, UInt32 size);
			
			UInt32 read(Buffer &data, UInt32 size);
			StdioInputFile &read(Buffer &b);
			StdioInputFile &readAll(Buffer &b);
			
			UInt32 size();
			UInt32 tell();
			StdioInputFile &seek(UInt32 _pos);
			StdioInputFile &seekEnd();
			StdioInputFile &seekBegin();
			StdioInputFile &seekStep(UInt32 _step);
			StdioInputFile &flush();
			
			bool eof();
	};

};

#endif
