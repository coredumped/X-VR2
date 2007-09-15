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
#include"config.h"
#include"xvr2config.h"
#include"FileException.h"
#include"MessageStrings.h"
#include<cerrno>

namespace xvr2 {

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
}


