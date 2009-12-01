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
#include"RawSocketOutputStream.h"
#include<cerrno>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/poll.h>
#include<fcntl.h>
#include<unistd.h>

namespace xvr2 {
	namespace Net {

		RawSocketOutputStream::RawSocketOutputStream():RawOutputStream(){
		}

		RawSocketOutputStream::~RawSocketOutputStream(){
			close();
		}

		RawSocketOutputStream::RawSocketOutputStream(int __fd):RawOutputStream(__fd){
		}

		RawSocketOutputStream::RawSocketOutputStream(const String &fname){
			throw InvalidSocket();
		}

		void RawSocketOutputStream::open(int __fd){
			RawOutputStream::open(__fd);
		}

		void RawSocketOutputStream::open(const String &fname) throw(InvalidSocket){
			throw InvalidSocket();
		}

		void RawSocketOutputStream::close(){
			if(_fd != 1 && _a_close == true){
				if(::shutdown(_fd, SHUT_WR) == -1){
					throw SystemException(errno);
				}
			}
		}

		void RawSocketOutputStream::setFlags(int f){
			flags = f;
		}

		RawSocketOutputStream &RawSocketOutputStream::write(void *data, UInt32 size){
			if(::send(_fd, data, size, flags) == -1){
				throw StreamException(errno);
			}
			return *this;
		}

		void RawSocketOutputStream::flush(){
		}

		FileSizeT RawSocketOutputStream::size(){
			return 0;
		}

		bool RawSocketOutputStream::eof(){
			return true;
		}

		bool RawSocketOutputStream::ready(int timeout){
			int r;
			bool ret = false;
			struct pollfd d = { _fd, POLLOUT, 0 };
			r = poll(&d, 1, timeout);
			if(r == -1){
				throw SocketException(errno);
			}
			else if(r > 0){
				if(d.revents & POLLOUT == POLLOUT){
					ret = true;
				}
			}
			return ret;
		}

	};
};

