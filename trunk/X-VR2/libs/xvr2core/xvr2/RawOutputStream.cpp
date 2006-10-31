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
#include"RawOutputStream.h"
#include<cerrno>
#include<sys/types.h>
#include<sys/poll.h>
#include<fcntl.h>
#include<unistd.h>

namespace xvr2 {
	RawOutputStream::RawOutputStream(){
		//As a default initialize it to be the stdout
		_fd = 1;
	}

	RawOutputStream::~RawOutputStream(){
		close();
	}

	RawOutputStream::RawOutputStream(int __fd){
		open(__fd);
	}

	RawOutputStream::RawOutputStream(const String &fname){
		open(fname);
	}

	void RawOutputStream::open(int __fd){
		_fd = __fd;
		_a_close = false;
	}

	void RawOutputStream::open(const String &fname){
		_fd = ::open(fname.toCharPtr(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if(_fd == -1) throw SystemException(errno);
		_a_close = true;
	}

	void RawOutputStream::close(){
		if(_fd != 0 && _a_close == true){
			::close(_fd);
		}
	}


	int RawOutputStream::fd(){
		return _fd;

	}

	RawOutputStream &RawOutputStream::write(void *data, UInt32 size){
		if(::write(_fd, data, size) == -1){
			throw StreamException(errno);
		}
		return *this;
	}

	void RawOutputStream::flush(){
		if(fsync(fd()) == -1){
			throw StreamException(errno);
		}
	}

	FileSizeT RawOutputStream::size(){
		flush();
		return RawStreamInterface::size();
	}

	bool RawOutputStream::eof(){
		return true;
	}

	bool RawOutputStream::ready(int timeout){
		int r;
		bool ret = false;
		struct pollfd d = { _fd, POLLOUT, 0 };
		r = poll(&d, 1, timeout);
		if(r == -1){
			throw StreamException(errno);
		}
		else if(r > 0){
			if(d.revents & POLLOUT == POLLOUT){
				ret = true;
			}
		}
		return ret;
	}
};

