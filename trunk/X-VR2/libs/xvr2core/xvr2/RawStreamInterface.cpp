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
#include"RawStreamInterface.h"
#include<cerrno>
#include<sys/types.h>
#include<sys/stat.h>

namespace xvr2 {

	FileSizeT RawStreamInterface::size(){
		struct stat buf;
		if(fstat(_fd, &buf) == -1){
			throw StreamException(errno);
		}
		return buf.st_size;
	}

	static const FileOffsetT __seek_failure_code = (FileOffsetT)-1;

	FileOffsetT RawStreamInterface::tell(){
		FileOffsetT ret;
		ret = lseek(_fd, 0, SEEK_CUR);
		if(ret == __seek_failure_code){
			throw StreamException(errno);
		}
		return ret;
	}

	bool RawStreamInterface::opened(){
		return _is_opened;
	}
};

