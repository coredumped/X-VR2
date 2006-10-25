#ifndef __XVR2_STDIOINTERFACE_H__
#define __XVR2_STDIOINTERFACE_H__
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/SystemException.h>
#include<xvr2/StreamInterface.h>
#include<cstdio>

namespace xvr2 {
	/** TODO: Document this class */
	class StdioInterface : public StreamInterface4G {
		private:
		protected:
			FILE *_fptr;
			void _close();
			void _open(const String &fname, const String &mode);
			bool _opened();
			size_t _read(void *_data, size_t __bytes);
			size_t _write(const void *_data, size_t __bytes);
			size_t computeSize();
			void _seek(UInt32 _pos, UInt32 _from);
			void _seek(UInt32 _pos);
			void _seekBegin();
			void _seekEnd();
			void _seekStep(UInt32 step);
			UInt32 _tell();
			size_t _fsize;
			bool _eof();
			void _flush();
		public:
			StdioInterface(){
				_fptr = 0;
				_fsize = 0;
			}
			FILE *cFILE() const {
				return _fptr;
			}
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
