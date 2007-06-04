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
#include"config.h"
#include"xvr2config.h"
#include"FileException.h"
#include"MessageStrings.h"
#include<cerrno>

namespace xvr2 {
	FileException::FileException(){
		description = (char *)xvr2::excepFile;
	}

	FeatureNotAvailableOnPipesOrSocket::FeatureNotAvailableOnPipesOrSocket(){
		description = (char *)xvr2::excepFeatureNotAvailableOnPipesOrSocket;
	}

	FileNotOpened::FileNotOpened(){
		description = (char *)xvr2::excepFileNotOpened;
	}

	FileExists::FileExists(){
		description = (char *)xvr2::excepFileExists;
	}

	ThisIsADirectory::ThisIsADirectory(){
		description = (char *)xvr2::excepThisIsADirectory;
	}

	PermissionDenied::PermissionDenied(){
		description = (char *)xvr2::excepPermissionDenied;
	}

	FilenameTooLong::FilenameTooLong(){
		description = (char *)xvr2::excepFilenameTooLong;
	}

	FileOrDirectoryNotFound::FileOrDirectoryNotFound(){
		description = (char *)xvr2::excepFileOrDirectoryNotFound;
	}

	ThisIsNotADirectory::ThisIsNotADirectory(){
		description = (char *)xvr2::excepThisIsNotADirectory;
	}

	UnableToWriteOnReadOnlyFile::UnableToWriteOnReadOnlyFile(){
		description = (char *)xvr2::excepUnableToWriteOnReadOnlyFile;
	}

	UnableToWriteOnRunningExecutableFile::UnableToWriteOnRunningExecutableFile(){
		description = (char *)xvr2::excepUnableToWriteOnRunningExecutableFile;
	}

	FilenameExceedsAddressSpace::FilenameExceedsAddressSpace(){
		description = (char *)xvr2::excepFilenameExceedsAddressSpace;
	}

	TooManySymlinks::TooManySymlinks(){
		description = (char *)xvr2::excepTooManySymlinks;
	}

	NotEnoughStorageSpace::NotEnoughStorageSpace(){
		description = (char *)xvr2::excepNotEnoughStorageSpace;
	}

	NotEnoughKernelMemory::NotEnoughKernelMemory(){
		description = (char *)xvr2::excepNotEnoughKernelMemory;
	}

	MaximumNumberOfOpenFilesForThisProcess::MaximumNumberOfOpenFilesForThisProcess(){
		description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisProcess;
	}

	MaximumNumberOfOpenFilesForThisSystem::MaximumNumberOfOpenFilesForThisSystem(){
		description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisSystem;
	}


	WriteWillBlock::WriteWillBlock(){
		description = (char *)xvr2::excepWriteWillBlock;
	}

	FileTooBig::FileTooBig(){
	        description = (char *)xvr2::excepFileTooBig;
	}

	FileNotFound::FileNotFound(){
	        description = (char *)xvr2::excepFileNotFound;
	}

	static const char *__invfd = "Invalid file descriptor given";
	InvalidFileDescriptor::InvalidFileDescriptor():FileException(EBADF){
	        description = (char *)__invfd;
		_fd = -1;
	}
	InvalidFileDescriptor::InvalidFileDescriptor(int __fd):FileException(EBADF){
	        description = (char *)__invfd;
		_fd = __fd;
	}
	int InvalidFileDescriptor::fd(){
		return _fd;
	}
};


