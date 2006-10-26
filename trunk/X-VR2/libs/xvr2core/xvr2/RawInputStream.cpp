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
#include<fcntl.h>

namespace xvr2 {

	RawInputStream::RawInputStream(){
		//Initialize to the standard input stream, just because I want it.
		_fd = 0;
	}

	RawInputStream::~RawInputStream(){
		close();
	}

	RawInputStream::RawInputStream(int __fd){
		_fd = __fd;
	}

	RawInputStream::RawInputStream(const String &fname){
		_fd = ::open(fname.toCharPtr(), O_RDONLY);
		if(_fd == -1) throw SystemException(errno);
		_a_close = true;
	}

	void RawInputStream::close(){
		if(_fd != 0 && _a_close == true){
			::close(_fd);
		}
	}

	void RawInputStream::open(int __fd){
		_a_close = false;
		_fd = __fd;
	}

	void RawInputStream::open(const String &fname){
		_fd = ::open(fname.toCharPtr(), O_RDONLY);
		if(_fd == -1) throw SystemException(errno);
		_a_close = true;
	}


	UInt32 RawInputStream::read(void *data, UInt32 size){
		Int32 ret = ::read(_fd, data, size);
		if(ret == -1){
			throw SystemException(errno);
		}
		return (UInt32)ret;
	}

	int RawInputStream::fd(){
		return _fd;
	}

};

