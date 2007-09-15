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
}

