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
#include"RawSocketInputStream.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<cerrno>

namespace xvr2 {
	namespace Net {

		RawSocketInputStream::RawSocketInputStream():RawInputStream(){
		}

		RawSocketInputStream::~RawSocketInputStream(){
		}

		RawSocketInputStream::RawSocketInputStream(int __fd):RawInputStream(__fd){
		}

		RawSocketInputStream::RawSocketInputStream(const String &fname):RawInputStream(){
			throw InvalidSocket();
		}

		void RawSocketInputStream::open(int __fd){
			RawInputStream::open(__fd);
		}

		void RawSocketInputStream::open(const String &fname){
			throw InvalidSocket();
		}

		void RawSocketInputStream::close(){
			::shutdown(_fd, SHUT_RD);
		}
		void RawSocketInputStream::setFlags(int _f){
			flags = _f;
		}

		UInt32 RawSocketInputStream::read(void *data, UInt32 size){
			/*if(handles_timeouts && timeout_msecs > 0){
				if(!ready(timeout_msecs)){
					throw RawInputStreamTimeoutException(fd(), timeout_msecs);
				}
			}*/
			Int32 ret = ::recv(_fd, data, size, flags);
			if(ret == -1){
				switch(errno){
					case ENOTSOCK:
						throw InvalidSocket(_fd);
						break;
					default:
						throw NetworkException(errno);
				}
			}
			return (UInt32)ret;
		}

		bool RawSocketInputStream::eof(){
			return (ready())?false:true;
		}

		void RawSocketInputStream::seek(FileOffsetT) throw (StreamIsNotSeekable){
			throw xvr2::StreamIsNotSeekable();
		}

		void RawSocketInputStream::seekEnd() throw (StreamIsNotSeekable){
			throw xvr2::StreamIsNotSeekable();
		}

		void RawSocketInputStream::seekBegin() throw (StreamIsNotSeekable){
			throw xvr2::StreamIsNotSeekable();
		}
		void RawSocketInputStream::seekStep(FileOffsetT) throw (StreamIsNotSeekable){
			throw xvr2::StreamIsNotSeekable();
		}

	};
};

