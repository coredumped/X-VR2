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
	}

	RawInputStream::~RawInputStream(){
		close();
	}

	RawInputStream::RawInputStream(int __fd){
		/*_fd = __fd;
		reached_eof = false;
		_is_opened = true;*/
		open(__fd);
	}

	RawInputStream::RawInputStream(const String &fname){
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
		struct pollfd d = { _fd, POLLIN | POLLPRI, 0 };
		r = poll(&d, 1, 0);
		if(r == -1){
			throw StreamException(errno);
		}
		else if(r > 0){
			if(d.revents & POLLIN == POLLIN || d.revents & POLLPRI == POLLPRI){
				ret = true;
			}
		}
		return ret;
	}
};

