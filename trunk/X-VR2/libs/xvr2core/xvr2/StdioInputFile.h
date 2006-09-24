/* $Id$ */
#ifndef __XVR2_STDIOINPUTFILE_H__
#define __XVR2_STDIOINPUTFILE_H__

#include<xvr2/FileInterface.h>
#include<xvr2/StdioInterface.h>
#include<xvr2/String.h>
#include<cstdio>

namespace xvr2 {

	class StdioInputFile : public ReadableFile, public StdioInterface {
		public:
			StdioInputFile();
			StdioInputFile(const String &fname);
			StdioInputFile(FILE *__f);
			void open(const String &path);
			void close();
			bool opened();
			virtual ~StdioInputFile();
			UInt32 read(void *data, UInt32 size);
			
			UInt32 size();
			UInt32 tell();
			StdioInputFile &seek(UInt32 _pos);
			StdioInputFile &seekEnd();
			StdioInputFile &seekBegin();
			StdioInputFile &seekStep(UInt32 _step);
			StdioInputFile &flush();
	};

};

#endif
