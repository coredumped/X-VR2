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
#include"Object.h"
#include"String.h"
#include"StreamInterface.h"

namespace xvr2 {
	StreamInterface::StreamInterface(){
	}
	StreamInterface::~StreamInterface(){
	}


	// BEGIN READABLE FILE
	ReadableStream &ReadableStream::operator >> (UInt32 n){
		read((void *)&n, sizeof(UInt32));
		return *this;
	}

	ReadableStream &ReadableStream::operator >> (double n){
		read((void *)&n, sizeof(double));
		return *this;
	}

	ReadableStream &ReadableStream::operator >> (UInt64 n){
		read((void *)&n, sizeof(UInt64));
		return *this;
	}

	UInt32 ReadableStream::read(UInt32 n){
		return read((void *)&n, sizeof(UInt32));
	}

	UInt32 ReadableStream::read(double n){
		return read((void *)&n, sizeof(double));
	}

	UInt32 ReadableStream::read(UInt64 n){
		return read((void *)&n, sizeof(UInt64));
	}

	//UInt32 ReadableStream::read(void *data, UInt32 size) = 0;
	UInt32 ReadableStream::read(Buffer &data, UInt32 ___size){
		UInt32 _siz;
		UInt8 *buf = new UInt8[___size];
		_siz = read((void *)buf, ___size);
		data.refTo(buf, _siz, true);
		return _siz;
	}

	ReadableStream &ReadableStream::read(Buffer &b){
		read(b, size() - tell());
		return *this;
	}

	ReadableStream &ReadableStream::readAll(Buffer &b){
		seekBegin();
		read(b, size());
		return *this;
	}

	void ReadableStream::flush(){
		throw StreamIsNotFlushable();
	}
	// END READABLE FILE


	// BEGIN WRITEABLE FILE
	WriteableStream &WriteableStream::operator << (const Buffer &b){
		write((void *)b.data(), b.size());
		return *this;
	}

	WriteableStream &WriteableStream::operator << (const String &s){
		write((void *)s.toCharPtr(), s.size());
		return *this;
	}

	//UInt32 WriteableStream::write(void *data, UInt32 size) = 0;
	WriteableStream &WriteableStream::write(const Buffer &data){
		write((void *)data.data(), data.size());
		return *this;
	}

	WriteableStream &WriteableStream::write(const String &s){
		write((void *)s.toCharPtr(), s.size());
		return *this;
	}

	void WriteableStream::seek(FileOffsetT _pos){
		throw StreamIsNotSeekable();
	}

	void WriteableStream::seekEnd(){
		throw StreamIsNotSeekable();
	}

	void WriteableStream::seekBegin(){
		throw StreamIsNotSeekable();
	}

	void WriteableStream::seekStep(FileOffsetT _step){
		throw StreamIsNotSeekable();
	}

	// END WRITEABLE FILE

}

