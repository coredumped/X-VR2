/* $Id$ */
#include"File.h"
#include<fstream>

namespace xvr2 {
	using std::fstream;
	File::File():std::fstream(){
		_fsize = 0;
	}
	File::File(const String &path, const FileOpenMode mode):std::fstream(path.toCharPtr()){
		_fsize = 0;
		open(path, mode);
	}
	File::~File(){
		if(opened()){
			close();
		}
	}
	/*void File::open(const FileOpenMode mode){
		switch(mode){
			case READ_ONLY:
				fstream::open(std::fstream::in);
				break;
			case WRITE_ONLY:
				fstream::open(std::fstream::out);
				break;
			case APPEND:
				fstream::open(std::fstream::out | std::fstream::app);
				break;
			case READ_WRITE:
			default:
				fstream::open(std::fstream::in|std::fstream::out);
		}
	}*/
	void File::open(const String &path, const FileOpenMode mode){
		switch(mode){
			case READ_ONLY:
				fstream::open(path.toCharPtr(), std::fstream::in);
				break;
			case WRITE_ONLY:
				fstream::open(path.toCharPtr(), std::fstream::out);
				break;
			case APPEND:
				fstream::open(path.toCharPtr(), std::fstream::out | std::fstream::app);
				break;
			case READ_WRITE:
			default:
				fstream::open(path.toCharPtr(), std::fstream::in|std::fstream::out);
		}
	}
	void File::close(){
		fstream::close();
	}
	const File &File::operator << (const Buffer &data){
		fstream::write((const char *)data.data(), data.size());
		return *this;
	}
	const File &File::operator << (const String &data){
		fstream::write(data.toCharPtr(), data.size());
		return *this;
	}
	const File &File::write(const Buffer &data){
		fstream::write((const char *)data.data(), data.size());
		return *this;
	}
	const File &File::write(const String &data){
		fstream::write(data.toCharPtr(), data.size());
		return *this;
	}
	File &File::operator >> (UInt32 n){
		fstream::read((char *)&n, sizeof(UInt32));
		return *this;
	}
	File &File::operator >> (double n){
		fstream::read((char *)&n, sizeof(double));
		return *this;
	}
	File &File::operator >> (UInt64 n){
		fstream::read((char *)&n, sizeof(UInt64));
		return *this;
	}
	UInt32 File::read(UInt32 n){
		UInt32 p1 = tell();
		fstream::read((char *)&n, sizeof(UInt32));
		return tell() - p1 + 1;
	}
	UInt32 File::read(double n){
		UInt32 p1 = tell();
		fstream::read((char *)&n, sizeof(double));
		return tell() - p1 + 1;
	}
	UInt32 File::read(UInt64 n){
		UInt32 p1 = tell();
		fstream::read((char *)&n, sizeof(UInt64));
		return tell() - p1 + 1;
	}
	UInt32 File::read(void *data, int __size){
		UInt32 p1 = tell();
		fstream::read((char *)data, __size);
		return tell() - p1 + 1;
	}
	UInt32 File::read(Buffer &data, int size){
		UInt32 _siz;
		UInt8 *buf = new UInt8(size);
		_siz = read(buf, size);
		data.refTo(buf, _siz);
		return _siz;
	}
	Buffer &File::read(){
	}
	Buffer &File::readAll(){
	}
	bool File::opened(){
		return is_open();
	}
	UInt32 File::size(){
		if(_fsize == 0){
			UInt32 _pos = tell();
			seekEnd();
			_fsize = tell();
			seek(_pos);
		}
		return _fsize;
	}
	UInt32 File::tell(){
		return fstream::tellg();
	}
	File &File::seek(UInt32 _pos){
		fstream::seekg(_pos, std::ios::beg);
		return *this;
	}
	File &File::seekEnd(){
		fstream::seekg(0, std::ios::end);
		return *this;
	}
	File &File::seekBegin(){
		fstream::seekg(0, std::ios::beg);
		return *this;
	}
	File &File::seekStep(UInt32 _step){
		fstream::seekg(_step, std::ios::cur);
		return *this;
	}
	File &File::flush(){
		fstream::flush();
		return *this;
	}
};
