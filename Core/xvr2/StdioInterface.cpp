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
	
	FileSizeT StdioInterface::size(){
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
	
	void StdioInterface::_seek(FileOffsetT _pos, UInt32 _from){
#ifdef XVR2_STDIO_PARANOID	
		if(!_opened()) throw FileNotOpened();
#endif
		if(fseek(_fptr, _pos, _from) != 0) throw SystemException(errno);
	}
	
	void StdioInterface::seek(FileOffsetT _pos){
		_seek(_pos, SEEK_SET);
	}
	
	void StdioInterface::seekBegin(){
		_seek(0, SEEK_SET);
	}
	
	void StdioInterface::seekEnd(){
		_seek(0, SEEK_END);
	}
	
	void StdioInterface::seekStep(FileOffsetT step){
		_seek(step, SEEK_CUR);
	}
	
	FileOffsetT StdioInterface::tell(){
		FileOffsetT _tx;
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		if((_tx = ftell(_fptr)) == -1) throw SystemException(errno);
		return _tx;
	}
	
	bool StdioInterface::eof(){
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		return (feof(_fptr) == 0)?false:true;
	}
	
	void StdioInterface::flush(){
#ifdef XVR2_STDIO_PARANOID
		if(!_opened()) throw FileNotOpened();
#endif
		if(fflush(_fptr) != 0) throw SystemException(errno);
	}
	
	StdioInterfaceException::StdioInterfaceException(int _code) : SystemException(_code){	}
	
}
