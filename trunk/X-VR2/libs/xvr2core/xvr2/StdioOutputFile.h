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

#ifndef __XVR2_STDIO_OUTPUT_FILE_H__
#define __XVR2_STDIO_OUTPUT_FILE_H__
#include<xvr2/Buffer.h>
#include<xvr2/StreamInterface.h>
#include<xvr2/StdioInterface.h>
#include<xvr2/String.h>
#include<cstdio>

namespace xvr2 {
	/** TODO: Document this class */
	class StdioOutputFile : public WriteableStream, private StdioInterface {
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
			
			FileSizeT size();
			FileOffsetT tell();
			void seek(UInt32 _pos);
			void seekEnd();
			void seekBegin();
			void seekStep(UInt32 _step);
			void flush();
			
			bool eof();
	};
};

#endif /*STDIOOUTPUTFILE_H_*/

