/* $Id$ */
#include"Object.h"
#include"String.h"
#include"FileInterface.h"

namespace xvr2 {
// BEGIN READABLE FILE
ReadableFile &ReadableFile::operator >> (UInt32 n){
	read((void *)&n, sizeof(UInt32));
	return *this;
}

ReadableFile &ReadableFile::operator >> (double n){
	read((void *)&n, sizeof(double));
	return *this;
}

ReadableFile &ReadableFile::operator >> (UInt64 n){
	read((void *)&n, sizeof(UInt64));
	return *this;
}

UInt32 ReadableFile::read(UInt32 n){
	return read((void *)&n, sizeof(UInt32));
}

UInt32 ReadableFile::read(double n){
	return read((void *)&n, sizeof(double));
}

UInt32 ReadableFile::read(UInt64 n){
	return read((void *)&n, sizeof(UInt64));
}

//UInt32 ReadableFile::read(void *data, UInt32 size) = 0;
UInt32 ReadableFile::read(Buffer &data, UInt32 ___size){
	UInt32 _siz;
	UInt8 *buf = new UInt8[___size];
	_siz = read((void *)buf, ___size);
	data.refTo(buf, _siz, true);
	return _siz;
}

ReadableFile &ReadableFile::read(Buffer &b){
	read(b, size() - tell());
	return *this;
}

ReadableFile &ReadableFile::readAll(Buffer &b){
	seekBegin();
	read(b, size());
	return *this;
}
// END READABLE FILE


// BEGIN WRITEABLE FILE
WriteableFile &WriteableFile::operator << (const Buffer &b){
	write((void *)b.data(), b.size());
	return *this;
}

WriteableFile &WriteableFile::operator << (const String &s){
	write((void *)s.toCharPtr(), s.size());
	return *this;
}

//UInt32 WriteableFile::write(void *data, UInt32 size) = 0;
WriteableFile &WriteableFile::write(const Buffer &data){
	write((void *)data.data(), data.size());
	return *this;
}

WriteableFile &WriteableFile::write(const String &s){
	write((void *)s.toCharPtr(), s.size());
	return *this;
}
// END WRITEABLE FILE

};

