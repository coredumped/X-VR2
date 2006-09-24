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
	
	UInt32 StdioInputFile::size(){
		return computeSize();	
	}
	
	UInt32 StdioInputFile::tell(){
		return _tell();
	}
	
	StdioInputFile &StdioInputFile::seek(UInt32 _pos){
		_seek(_pos);
		return *this;
	}
	
	StdioInputFile &StdioInputFile::seekEnd(){
		_seekEnd();
		return *this;
	}
	
	StdioInputFile &StdioInputFile::seekBegin(){
		_seekBegin();
		return *this;
	}
	
	StdioInputFile &StdioInputFile::seekStep(UInt32 _step){
		_seekStep(_step);
		return *this;
	}
	
	//Input reading can't be flushed
	StdioInputFile &StdioInputFile::flush(){
		return *this;
	}
}
