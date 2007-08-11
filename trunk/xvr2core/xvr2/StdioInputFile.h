/* $Id$ */
#ifndef __XVR2_STDIOINPUTFILE_H__
#define __XVR2_STDIOINPUTFILE_H__

#include<xvr2/StreamInterface.h>
#include<xvr2/StdioInterface.h>
#include<xvr2/String.h>
#include<cstdio>

namespace xvr2 {

	class StdioInputFile : public ReadableStream, public StdioInterface {
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
			
			void flush();
	};

};

#endif

