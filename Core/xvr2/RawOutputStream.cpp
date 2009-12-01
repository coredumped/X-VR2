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
		_a_close = false;
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
		if(_fd != 1 && _a_close == true){
			if(::close(_fd) == -1){
				throw SystemException(errno);
			}
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
}

