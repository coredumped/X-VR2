/* $Id$
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
#ifndef __XVR2_FILE_EXCEPTION_H__
#define __XVR2_FILE_EXCEPTION_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/SystemException.h>

namespace xvr2 {
	/** \class FileExists FileException.h <xvr2/FileException.h>
	 *  \brief Exception thrown when the file to be used alreadyeady exists.
	 *  This exception will be thrown only if you enable the checking 
	 *  while creating a new file in write or append mode. */
	class FileExists:public FileException{
		public:
			/** Default constructor */
			FileExists();
	};
	/** \class FeatureNotAvailableOnPipesOrSocket CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is thrown when u are attempting to execute an
	 *  operation that is only valid to common files and for PIPEs
	 *  or Sockets */
	class FeatureNotAvailableOnPipesOrSocket:public FileException{
		public:
			/** Default constructor */
			FeatureNotAvailableOnPipesOrSocket();
	};

	/** \class ThisIsADirectory CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are attempting to open
	 *  a file but the given filename corresponds to a directory. */
	class ThisIsADirectory:public FileException{
		public:
			/** Default constructor */
			ThisIsADirectory();
	};
	/** \class PermissionDenied CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if the current process does not
	 *  own the rights to do a specific operation on this file. */
	class PermissionDenied:public FileException{
		public:
			/** Default constructor */
			PermissionDenied();
	};
	/** \class FilenameTooLong CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are attempting to open a 
	 *  very large filename. */
	class FilenameTooLong:public FileException{
		public:
			/** Default constructor */
			FilenameTooLong();
	};
	/** \class FileOrDirectoryNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are opening a file for
	 *  reading and the currently opened file does not exist. */
	class FileOrDirectoryNotFound:public FileException{
		public:
			/** Default constructor */
			FileOrDirectoryNotFound();
	};
	/** \class ThisIsNotADirectory CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are attempting to open a 
	 *  directory and the given filename is not a directory. */
	class ThisIsNotADirectory:public FileException{
		public:
			/** Default constructor */
			ThisIsNotADirectory();
	};
	/** \class FileNotOpened CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you attempt to execute an
	 *  operation on a non-opened file. */
	class FileNotOpened:public FileException{
		public:
			/** Default constructor */
			FileNotOpened();
	};
	/** \class UnableToWriteOnReadOnlyFile CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are trying to write on a
	 *  read only opened file. */
	class UnableToWriteOnReadOnlyFile:public FileException{
		public:
			/** Default constructor */
			UnableToWriteOnReadOnlyFile();
	};
	/** \class UnableToWriteOnRunningExecutableFile CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are trying to write on an
	 *  executable file of process which is already running. */
	class UnableToWriteOnRunningExecutableFile:public FileException{
		public:
			/** Default constructor */
			UnableToWriteOnRunningExecutableFile();
	};
	/** \class FilenameExceedsAddressSpace CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if you are trying to reach file 
	 *  which is outside of the address provided by its parent directory. */
	class FilenameExceedsAddressSpace:public FileException{
		public:
			/** Default constructor */
			FilenameExceedsAddressSpace();
	};
	/** \class TooManySymlinks CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if the file you are trying to read
	 *  is the last symlink in a very large chain. */
	class TooManySymlinks:public FileException{
		public:
			/** Default constructor */
			TooManySymlinks();
	};
	/** \class NotEnoughStorageSpace CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception will be thrown only if there is not enough room to 
	 *  to open this file. */
	class NotEnoughStorageSpace:public FileException{
		public:
			/** Default constructor */
			NotEnoughStorageSpace();
	};
	/** \class MaximumNumberOfOpenFilesForThisProcess CoreExceptions.h <xvr2/CoreExceptions.h>
	 * This exception will be thrown only if the maximum number of opened
	 * files. */
	class MaximumNumberOfOpenFilesForThisProcess:public FileException{
		public:
			/** Default constructor */
			MaximumNumberOfOpenFilesForThisProcess();
	};
	/** @class MaximumNumberOfOpenFilesForThisSystem FileException.h <xvr2/FileException.h>
	 *  This exception will be thrown only if this system has reached the
	 *  maximum number of opened files that the kernel can handle */
	class MaximumNumberOfOpenFilesForThisSystem:public FileException{
		public:
			/**
			 * Default constructor
			 */
			MaximumNumberOfOpenFilesForThisSystem();
	};

	/** \class FileTooBig CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  This exception is thrown whenever you attempt to write pass the maximum offset 
	 *  allowed or while writing a file will make it grow pass the implementation 
	 *  defined size for the current OS. */
	class FileTooBig:public FileException{
	        public:
	                /** Default constructor */
	                FileTooBig();
	};

	/** \class WriteWillBlock CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  The file was opened with NON-BLOCKING feature but if u write the process will 
	 *  block every I/O. */
	class WriteWillBlock:public FileException{
		public:
			/** Default constructor */
			WriteWillBlock();
	};

	/** \class FileNotFound CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  Unable to find the requested file. */
	class FileNotFound:public FileException{
		public:
			/** Default constructor */
			FileNotFound();
	};

	/** \class InvalidFileDescriptor FileException.h <xvr2/FileException.h>
	 *  Exception thrown when the given value is not actually a file descriptor. */
	class InvalidFileDescriptor:public FileException {
		private:
			int _fd;
		public:
			InvalidFileDescriptor();
			InvalidFileDescriptor(int __fd);
			/** Value of the wrong file descriptor. */
			int fd();
	};

};


#endif
