/*
 * $Id$
 */
#ifndef __XVR2_FILE_EXCEPTION_H__
#define __XVR2_FILE_EXCEPTION_H__
#include<xvr2/Exception.h>
#include<xvr2/IOException.h>

namespace xvr2 {

	/**
	 * You will only be seeing this exception if a generic (undetermined)
	 * exception has occurred on a file-based class
	 */
	class FileException:public IOException{
		public:
			/**
			 * Default constructor
			 */
			FileException();
	};

	/**
	 * This exception will be thrown only if you enable the checking while
	 * creating a new file in write or append mode */
	class FileExists:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileExists();
	};
	/** This exception is thrown when u are attempting to execute an
	 *  operation that is only valid to common files and for PIPEs
	 *  or Sockets */
	class FeatureNotAvailableOnPipesOrSocket:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FeatureNotAvailableOnPipesOrSocket();
	};

	/**
	 * This exception will be thrown only if you are attempting to open
	 * a file but the given filename corresponds to a directory
	 */
	class ThisIsADirectory:public FileException{
		public:
			/**
			 * Default constructor
			 */
			ThisIsADirectory();
	};
	/**
	 * This exception will be thrown only if the current process does not
	 * own the rights to do a specific operation on this file
	 */
	class PermissionDenied:public FileException{
		public:
			/**
			 * Default constructor
			 */
			PermissionDenied();
	};
	/**
	 * This exception will be thrown only if you are attempting to open a 
	 * very large filename
	 */
	class FilenameTooLong:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FilenameTooLong();
	};
	/**
	 * This exception will be thrown only if you are opening a file for
	 * reading and the currently opened file does not exist
	 */
	class FileOrDirectoryNotFound:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileOrDirectoryNotFound();
	};
	/**
	 * This exception will be thrown only if you are attempting to open a 
	 * directory and the given filename is not a directory
	 */
	class ThisIsNotADirectory:public FileException{
		public:
			/**
			 * Default constructor
			 */
			ThisIsNotADirectory();
	};
	/**
	 * This exception will be thrown only if you attempt to execute an
	 * operation on a non-opened file
	 */
	class FileNotOpened:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileNotOpened();
	};
	/**
	 * This exception will be thrown only if you are trying to write on a
	 * read only opened file
	 */
	class UnableToWriteOnReadOnlyFile:public FileException{
		public:
			/**
			 * Default constructor
			 */
			UnableToWriteOnReadOnlyFile();
	};
	/**
	 * This exception will be thrown only if you are trying to write on an
	 * executable file of process which is already running
	 */
	class UnableToWriteOnRunningExecutableFile:public FileException{
		public:
			/**
			 * Default constructor
			 */
			UnableToWriteOnRunningExecutableFile();
	};
	/**
	 * This exception will be thrown only if you are trying to reach file 
	 * which is outside of the address provided by its parent directory
	 */
	class FilenameExceedsAddressSpace:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FilenameExceedsAddressSpace();
	};
	/**
	 * This exception will be thrown only if the file you are trying to read
	 * is the last symlink in a very large chain
	 */
	class TooManySymlinks:public FileException{
		public:
			/**
			 * Default constructor
			 */
			TooManySymlinks();
	};
	/**
	 * This exception will be thrown only if there is not enough room to 
	 * to open this file
	 */
	class NotEnoughStorageSpace:public FileException{
		public:
			/**
			 * Default constructor
			 */
			NotEnoughStorageSpace();
	};
	/**
	 * This exception will be thrown only if there is not enough memory 
	 * for kernel use
	 */
	class NotEnoughKernelMemory:public IOException{
		public:
			/**
			 * Default constructor
			 */
			NotEnoughKernelMemory();
	};
	/**
	 * This exception will be thrown only if the maximum number of opened
	 * files
	 */
	class MaximumNumberOfOpenFilesForThisProcess:public FileException{
		public:
			/**
			 * Default constructor
			 */
			MaximumNumberOfOpenFilesForThisProcess();
	};
	/**
	 * This exception will be thrown only if this system has reached the
	 * maximum number of opened files that the kernel can handle
	 */
	class MaximumNumberOfOpenFilesForThisSystem:public FileException{
		public:
			/**
			 * Default constructor
			 */
			MaximumNumberOfOpenFilesForThisSystem();
	};

	/** This exception is thrown whenever you attempt to write pass the maximum offset allowed or while writing a file will make it grow pass the implementation defined size for the current OS. */
	class FileTooBig:public FileException{
	        public:
	                /**
	                 * Default constructor
	                 */
	                FileTooBig();
	};

	/** The file was opened with NON-BLOCKING feature but if u write the process will block every I/O */
	class WriteWillBlock:public FileException{
		public:
			/**
			 * Default constructor
			 */
			WriteWillBlock();
	};

	/** Unable to find the requested file */
	class FileNotFound:public FileException{
		public:
			/**
			 * Default constructor
			 */
			FileNotFound();
	};
};


#endif
