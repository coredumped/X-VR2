/* $Id$ */ 
#include"StdioInputFile.h"
#include"StdioInterface.h"
#include<cstdio>

namespace xvr2{

	StdioInputFile::StdioInputFile(){ ; }

	StdioInputFile::~StdioInputFile(){
		close();
	}

	StdioInputFile::StdioInputFile(const String &fname){
		StdioInterface::_open(fname.toCharPtr(), "r");
	}
	
	StdioInputFile::StdioInputFile(FILE *__f){
		_fptr = __f;
	}
	
	void StdioInputFile::open(const String &path){
		StdioInterface::_open(path.toCharPtr(), "r");
	}
	
	void StdioInputFile::close(){
		return StdioInterface::_close();
	}
	
	bool StdioInputFile::opened(){
		return StdioInterface::_opened();
	}
	
	UInt32 StdioInputFile::read(void *data, UInt32 _size){
		return _read(data, _size);
	}
	
	FileSizeT StdioInputFile::size(){
		return computeSize();	
	}
	
	FileOffsetT StdioInputFile::tell(){
		return _tell();
	}
	
	void StdioInputFile::seek(FileOffsetT _pos){
		_seek(_pos);
	}
	
	void StdioInputFile::seekEnd(){
		_seekEnd();
	}
	
	void StdioInputFile::seekBegin(){
		_seekBegin();
	}
	
	void StdioInputFile::seekStep(FileOffsetT _step){
		_seekStep(_step);
	}
	
	//Input reading can't be flushed
	void StdioInputFile::flush(){
	}
	
	bool StdioInputFile::eof(){
		return _eof();
	}
	
	UInt32 StdioInputFile::read(Buffer &data, UInt32 ___size){
		UInt32 _siz;
		UInt8 *buf = new UInt8[___size];
		_siz = read((void *)buf, ___size);
		data.refTo(buf, _siz, true);
		return _siz;
	}

	StdioInputFile &StdioInputFile::read(Buffer &b){
		read(b, size() - tell());
		return *this;
	}

	StdioInputFile &StdioInputFile::readAll(Buffer &b){
		seekBegin();
		read(b, size());
		return *this;
	}
}
