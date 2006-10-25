/* $Id$ */
#include"StreamInterface.h"
#include"StdioInterface.h"
#include"StdioOutputFile.h"

namespace xvr2 {
	
	StdioOutputFile::StdioOutputFile():WriteableStream(),StdioInterface(){
	}
			
	StdioOutputFile::StdioOutputFile(const String &fname, bool for_append){
		open(fname.toCharPtr(), for_append);
	}
	
	StdioOutputFile::StdioOutputFile(FILE *__f){
		_fptr = __f;
	}
	
	StdioOutputFile::~StdioOutputFile(){
		close();
	}
	
	void StdioOutputFile::open(const String &path){
		_open(path.toCharPtr(), "w");
	}
	
	void StdioOutputFile::open(const String &path, bool for_append){
		if(for_append){
			_open(path.toCharPtr(), "a");
		}
		else{
			_open(path.toCharPtr(), "w");
		}
	}
	
	void StdioOutputFile::close(){
		_close();
	}
	
	bool StdioOutputFile::opened(){
		return _opened();
	}
	
	StdioOutputFile &StdioOutputFile::operator << (const Buffer &b){
		write((void *)b.data(), b.size());
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::operator << (const String &s){
		write((void *)s.toCharPtr(), s.size());
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::write(void *data, UInt32 __size){
		_write(data, __size);
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::write(const Buffer &b){
		write((void *)b.data(), b.size());
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::write(const String &s){
		write((void *)s.toCharPtr(), s.size());
		return *this;
	}
	
	UInt32 StdioOutputFile::size(){
		return computeSize();	
	}
	
	UInt32 StdioOutputFile::tell(){
		return _tell();
	}
	
	StdioOutputFile &StdioOutputFile::seek(UInt32 _pos){
		_seek(_pos);
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::seekEnd(){
		_seekEnd();
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::seekBegin(){
		_seekBegin();
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::seekStep(UInt32 _step){
		_seekStep(_step);
		return *this;
	}
	
	StdioOutputFile &StdioOutputFile::flush(){
		_flush();
		return *this;
	}
	
	bool StdioOutputFile::eof(){
		return _eof();
	}
};
