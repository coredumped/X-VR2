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
#ifndef __XVR2_STDIOINTERFACE_H__
#define __XVR2_STDIOINTERFACE_H__
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/SystemException.h>
#include<xvr2/StreamInterface.h>
#include<cstdio>

namespace xvr2 {
	/** TODO: Document this class */
	class StdioInterface : public virtual StreamInterface {
		private:
		protected:
			FILE *_fptr;
			void _close();
			void _open(const String &fname, const String &mode);
			bool _opened();
			size_t _read(void *_data, size_t __bytes);
			size_t _write(const void *_data, size_t __bytes);
			void _seek(FileOffsetT _pos, UInt32 _from);
			FileSizeT _fsize;
		public:
			StdioInterface(){
				_fptr = 0;
				_fsize = 0;
			}
			FILE *cFILE() const {
				return _fptr;
			}
			virtual FileSizeT size();
			virtual FileOffsetT tell();
			void seek(FileOffsetT _pos);
			void seekBegin();
			void seekEnd();
			void seekStep(FileOffsetT step);
			bool eof();
			void flush();
	};
	
	/** TODO: Document this class */
	class StdioInterfaceException : public SystemException {
		private:
		protected:
		public:
			StdioInterfaceException(int _code);
	};
};

#endif
