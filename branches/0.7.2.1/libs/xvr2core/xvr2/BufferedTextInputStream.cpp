/* $Id$ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include"BufferedTextInputStream.h"
#include"StringBuffer.h"
#include"Memory.h"
#include"DebugConsole.h"

#ifndef BUFFERED_INPUT_STREAM_DEFAULT_BUFSIZE
#define BUFFERED_INPUT_STREAM_DEFAULT_BUFSIZE 1024
#endif

namespace xvr2 {

	static UInt32 __default_bufsize = BUFFERED_INPUT_STREAM_DEFAULT_BUFSIZE;
	
	BufferedTextInputStream::BufferedTextInputStream():RawInputStream(){
		_bufsize = __default_bufsize;
		_lterm = xvr2::NL;
		while(_bufsize % _lterm.size() != 0){
			_bufsize++;
		}
	}

	BufferedTextInputStream::BufferedTextInputStream(RawInputStream &input, const String &__lterm):RawInputStream(input.fd()){
		_bufsize = __default_bufsize;
		_lterm = __lterm;
		while(_bufsize % _lterm.size() != 0){
			_bufsize++;
		}
	}

	void BufferedTextInputStream::open(RawInputStream &input, const String &__lterm){
		RawInputStream::open(input.fd());
		_bufsize = __default_bufsize;
		_lterm = __lterm;
		while(_bufsize % _lterm.size() != 0){
			_bufsize++;
		}		
	}

	BufferedTextInputStream::~BufferedTextInputStream(){
	}

	void BufferedTextInputStream::setDefaultBufferSize(UInt32 _size){
		__default_bufsize = _size;
	}

	void BufferedTextInputStream::setBufferSize(UInt32 _size){
		_bufsize = _size;
		while(_bufsize % _lterm.size() != 0){
			_bufsize++;
		}
	}

	/*virtual UInt32 BufferedTextInputStream::read(void *data, UInt32 size){
		//Clear buffer first
		Memory::clearBuffer(buffer, _bufsize + 1);

		RawInputStream::read(buffer, _bufsize);
	}*/

	UInt32 BufferedTextInputStream::remaining(){
		return buffer.size();
	}

	void BufferedTextInputStream::operator>>(String &s){
		char _buf[_bufsize];
		char *bufptr = 0;
		s.clear();
		if(buffer.size() == 1 && buffer[0] == 0) buffer.clear();
		while(ready()){
			//_buf = new char[_bufsize];
			//Memory::clearBuffer(_buf, _bufsize);
			UInt32 siz = read(_buf, _bufsize);
#ifdef USE_DEBUG
			debugConsole << "BufferedTextInputStream: read1(fd=" << fd() << " siz=" << siz << " ) = " << _buf << xvr2::NL;
#endif
			buffer.eat(_buf, siz);
			//delete[] _buf;
		}
		if(buffer.equals(_lterm)){
			s.eat((char *)buffer.toCharPtr(), _lterm.size());
			buffer.clear();
		}
		else if(buffer.startsWith(_lterm)){
			s.eat((char *)buffer.toCharPtr(), _lterm.size());
			buffer.biteLeft(_lterm.size());
		}
		else if(buffer.size() > 0){
#ifdef USE_DEBUG
			debugConsole << "BufferedTextInputStream: buffer has: \"" << buffer << "\"" << xvr2::NL;
#endif
			bufptr = (char *)buffer.toCharPtr();
			while(buffer.size() > 0 && !buffer.startsWith(_lterm)){
				if(buffer[0] != 0) s.eat(buffer.toCharPtr(), 1);
				if(buffer.size() == 1){
					buffer.clear();
					return;
				}
				else{
					buffer.biteLeft(1);
				}
			}
			s.eat(buffer.toCharPtr(), _lterm.size());
			if(buffer.size() == _lterm.size()){
				buffer.clear();
			}
			else{
				buffer.biteLeft(_lterm.size());
			}
#ifdef USE_DEBUG
			debugConsole << "BufferedTextInputStream: s now has: \"" << s << "\"" << xvr2::NL;
#endif
		}
	}

};

