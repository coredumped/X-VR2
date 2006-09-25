/* $Id$ */
#include"StdioInterface.h"
#include"SystemException.h"
#include<cstdio>
#include<cerrno>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

namespace xvr2 {
	void StdioInterface::_close(){
		if(_fptr != 0){
			if(fclose(_fptr) != 0){
				throw SystemException(errno);
			}
			_fptr = 0;
		}
	}
	
	void StdioInterface::_open(const String &fname, const String &mode){
		_fptr = fopen(fname.toCharPtr(), mode.toCharPtr());
		if(_fptr == 0) throw SystemException(errno);
	}
	
	bool StdioInterface::_opened(){
		return (_fptr == 0)?false:true;
	}
	
	size_t StdioInterface::_read(void *_data, size_t __bytes){
		size_t ret;
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		ret = fread(_data, 1, __bytes, _fptr);
		if(ferror(_fptr)){
			throw StdioInterfaceException(errno);
		}
		return ret;
	}
	
	size_t StdioInterface::_write(const void *_data, size_t __bytes){
		size_t ret;
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		ret = fwrite(_data, 1, __bytes, _fptr);
		if(ferror(_fptr)){
			throw StdioInterfaceException(errno);
		}
		return ret;
	}
	
	size_t StdioInterface::computeSize(){
		if(_fsize == 0){
#ifdef XVR2_STDIO_PARANOID
			if(!_opened()) throw FileNotOpened();
#endif
			struct stat inf;
			if(fstat(fileno(_fptr), &inf) != 0){
				throw SystemException(errno);
			}
			_fsize = inf.st_size;	
		}		
		return _fsize;
	}
	
	void StdioInterface::_seek(UInt32 _pos, UInt32 _from){
#ifdef XVR2_STDIO_PARANOID	
		if(!_opened()) throw FileNotOpened();
#endif
		if(fseek(_fptr, _pos, _from) != 0) throw SystemException(errno);
	}
	
	void StdioInterface::_seek(UInt32 _pos){
		_seek(_pos, SEEK_SET);
	}
	
	void StdioInterface::_seekBegin(){
		_seek(0, SEEK_SET);
	}
	
	void StdioInterface::_seekEnd(){
		_seek(0, SEEK_END);
	}
	
	void StdioInterface::_seekStep(UInt32 step){
		_seek(step, SEEK_CUR);
	}
	
	UInt32 StdioInterface::_tell(){
		long _tx;
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		if((_tx = ftell(_fptr)) == -1) throw SystemException(errno);
		return (UInt32)_tx;
	}
	
	bool StdioInterface::_eof(){
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		return (feof(_fptr) == 0)?false:true;
	}
	
	void StdioInterface::_flush(){
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		if(fflush(_fptr) != 0) throw SystemException(errno);
	}
	
	StdioInterfaceException::StdioInterfaceException(int _code) : SystemException(_code){	}
	
};
