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
