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
#ifndef __XVR2_STDIO_OUTPUT_FILE_H__
#define __XVR2_STDIO_OUTPUT_FILE_H__
#include<xvr2/Buffer.h>
#include<xvr2/StreamInterface.h>
#include<xvr2/StdioInterface.h>
#include<xvr2/String.h>
#include<cstdio>

namespace xvr2 {
	
	/** @todo Document the StdioOutputFile class please */
	class StdioOutputFile : public WriteableStream, public StdioInterface {
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
			
			void seek(FileOffsetT _pos);
			void seekEnd();
			void seekBegin();
			void seekStep(FileOffsetT _step);
			
			bool eof();
	};
}

#endif /*STDIOOUTPUTFILE_H_*/

