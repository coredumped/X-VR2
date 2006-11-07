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

#ifndef BUFFERED_INPUT_STREAM_DEFAULT_BUFSIZE
#define BUFFERED_INPUT_STREAM_DEFAULT_BUFSIZE 1024
#endif

namespace xvr2 {

	static UInt32 __default_bufsize = BUFFERED_INPUT_STREAM_DEFAULT_BUFSIZE;

	BufferedTextInputStream::BufferedTextInputStream(RawInputStream &input, const String &__lterm):RawInputStream(input.fd()){
		_bufsize = __default_bufsize;
		_lterm = __lterm;
	}

	BufferedTextInputStream::~BufferedTextInputStream(){
	}

	void BufferedTextInputStream::setDefaultBufferSize(UInt32 _size){
		__default_bufsize = _size;
	}

	/*virtual UInt32 BufferedTextInputStream::read(void *data, UInt32 size){
		//Clear buffer first
		Memory::clearBuffer(buffer, _bufsize + 1);

		RawInputStream::read(buffer, _bufsize);
	}*/

	void BufferedTextInputStream::operator>>(String &s){
		char *_buf;
		char *bufptr = 0;
		s.clear();
		if(buffer.size() > 0){
			if(buffer.equals(_lterm)){
				s.eat((char *)buffer.toCharPtr(), _lterm.size());
				buffer.clear();
			}
			else if(buffer.startsWith(_lterm)){
				s.eat((char *)buffer.toCharPtr(), _lterm.size());
				buffer.biteLeft(_lterm.size());
			}
			else{
				bufptr = (char *)buffer.toCharPtr();
				int eaten = 0;
				while(buffer.size() > 0 && !buffer.startsWith(_lterm)){
					s.eat(buffer.toCharPtr(), 1);
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
				/*do{
					s.eat((char *)buffer.toCharPtr(), 1);
					buffer.biteLeft(1);
				} while(!buffer.startsWith(_lterm) && buffer.size() > _lterm.size());
				s.eat((char *)buffer.toCharPtr(), _lterm.size());*/
			}
		}
		else{
			bool keep_reading = true;
			while(_bufsize % _lterm.size() != 0){
				_bufsize++;
			}
			_buf = new char[_bufsize];
			do{
				Memory::clearBuffer(_buf, _bufsize);
				UInt32 siz = read(_buf, _bufsize);
				if(siz > 0){
					//Now the tricky part, lets read the _buf every _lterm.size()
					//steps until one of those steps is equals to _lterm, keep feeding
					//that to data
					bufptr = _buf;
					for(UInt32 i = 0; i < siz; i++){
						s.eat(bufptr, 1);
						if(strncmp(_lterm.toCharPtr(), bufptr, _lterm.size()) == 0){
							keep_reading = false;
							//Read all the remainings from bufptr to the end of the _buf
							//then assign it to line
							buffer.clear();
							buffer.eat(bufptr + _lterm.size(), siz - (i + 1));
							break;
						}
						bufptr += 1;
					}
				}
			}while(keep_reading);
			delete[] _buf;
		}
	}

};

