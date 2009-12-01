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
#include"RawInputStream.h"
#include<cstdlib>
#include<cerrno>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/poll.h>
#include<fcntl.h>
#include<unistd.h>

namespace xvr2 {

	RawInputStream::RawInputStream(){
		//Initialize to the standard input stream, just because I want it.
		_fd = 0;
		reached_eof = false;
		_is_opened = true;
		handles_timeouts = true;
	}

	RawInputStream::~RawInputStream(){
		close();
	}

	RawInputStream::RawInputStream(int __fd){
		/*_fd = __fd;
		reached_eof = false;
		_is_opened = true;*/
		handles_timeouts = true;
		open(__fd);
	}

	RawInputStream::RawInputStream(const String &fname){
		handles_timeouts = true;
		open(fname);
	}

	void RawInputStream::close(){
		if(_fd != 0 && _a_close == true){
			::close(_fd);
		}
	}

	void RawInputStream::open(int __fd){
		reached_eof = false;
		_a_close = false;
		_fd = __fd;
		_is_opened = true;
	}

	void RawInputStream::open(const String &fname){
		reached_eof = false;
		_fd = ::open(fname.toCharPtr(), O_RDONLY);
		if(_fd == -1){
			_is_opened = false;
			throw SystemException(errno);
		}
		_a_close = true;
		_is_opened = true;
	}


	UInt32 RawInputStream::read(void *data, UInt32 size){
		if(handles_timeouts && timeout_msecs > 0){
			if(!ready(timeout_msecs)){
				throw RawInputStreamTimeoutException(fd(), timeout_msecs);
			}
		}
		Int32 ret = ::read(_fd, data, size);
		if(ret == -1){
			throw SystemException(errno);
		}
		else if(ret == 0){
			reached_eof = true;
		}
		return (UInt32)ret;
	}

	int RawInputStream::fd(){
		return _fd;
	}

	bool RawInputStream::eof(){
		return reached_eof;
	}

	static const FileOffsetT __seek_failure_code2 = (FileOffsetT)-1;

	void RawInputStream::seek(FileOffsetT _pos){
		if(::lseek(fd(), _pos, SEEK_SET) == __seek_failure_code2){
			throw StreamException(errno);
		}
		reached_eof = false;
	}

	void RawInputStream::seekEnd(){
		if(::lseek(fd(), 0, SEEK_END) == __seek_failure_code2){
			throw StreamException(errno);
		}
		reached_eof = false;
	}

	void RawInputStream::seekBegin(){
		seek(0);
	}

	void RawInputStream::seekStep(FileOffsetT _step){
		if(::lseek(fd(), _step, SEEK_CUR) == __seek_failure_code2){
			throw StreamException(errno);
		}
		reached_eof = false;
	}

	bool RawInputStream::ready(int timeout){
		int r;
		bool ret = false;
		struct pollfd d;
		d.fd = fd();
		d.events = POLLIN | POLLPRI;
		errno = 0;
		r = poll(&d, 1, timeout);
		if(r == -1 && !(errno == EAGAIN || errno == EINTR)){
			throw StreamException(errno);
		}
		else if(r > 0){
			if(d.revents & POLLIN == POLLIN || d.revents & POLLPRI == POLLPRI){
				ret = true;
			}
		}
		return ret;
	}


	/////////////////////// RawInputStreamTimeoutException class ////////////////
	RawInputStreamTimeoutException::RawInputStreamTimeoutException(int __fd):StreamException(errno){
		_fd = __fd;
	}
	RawInputStreamTimeoutException::RawInputStreamTimeoutException(int __fd, int __msecs):StreamException(errno){
		_fd = __fd;
		_msecs = __msecs;
	}
	int RawInputStreamTimeoutException::fd(){
		return _fd; 
	}
	int RawInputStreamTimeoutException::millis(){
		return _msecs;
	}
}

