/*
 * $Id$
 */
#ifndef __XVR2_FILE_EXCEPTION_H__
#define __XVR2_FILE_EXCEPTION_H__
#include<Exception.h>
#include<IOException.h>

namespace xvr2 {
	namespace Exception{

		/**
		 * You will only be seeing this exception if a generic (undetermined)
		 * exception has occurred on a file-based class
		 */
		class File:public IO{
			public:
				/**
				 * Default constructor
				 */
				File();
		};

		/**
		 * This exception will be thrown only if you enable the checking while
		 * creating a new file in write or append mode */
		class FileExists:public File{
			public:
				/**
				 * Default constructor
				 */
				FileExists();
		};
		/** This exception is thrown when u are attempting to execute an
		 *  operation that is only valid to common files and for PIPEs
		 *  or Sockets */
		class FeatureNotAvailableOnPipesOrSocket:public File{
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
		class ThisIsADirectory:public File{
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
		class PermissionDenied:public File{
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
		class FilenameTooLong:public File{
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
		class FileOrDirectoryNotFound:public File{
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
		class ThisIsNotADirectory:public File{
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
		class FileNotOpened:public File{
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
		class UnableToWriteOnReadOnlyFile:public File{
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
		class UnableToWriteOnRunningExecutableFile:public File{
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
		class FilenameExceedsAddressSpace:public File{
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
		class TooManySymlinks:public File{
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
		class NotEnoughStorageSpace:public File{
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
		class NotEnoughKernelMemory:public IO{
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
		class MaximumNumberOfOpenFilesForThisProcess:public File{
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
		class MaximumNumberOfOpenFilesForThisSystem:public File{
			public:
				/**
				 * Default constructor
				 */
				MaximumNumberOfOpenFilesForThisSystem();
		};

		/** This exception is thrown whenever you attempt to write pass the maximum offset allowed or while writing a file will make it grow pass the implementation defined size for the current OS. */
		class FileTooBig:public File{
		        public:
		                /**
		                 * Default constructor
		                 */
		                FileTooBig();
		};

		/** The file was opened with NON-BLOCKING feature but if u write the process will block every I/O */
		class WriteWillBlock:public File{
			public:
				/**
				 * Default constructor
				 */
				WriteWillBlock();
		};

		/** Unable to find the requested file */
		class FileNotFound:public File{
			public:
				/**
				 * Default constructor
				 */
				FileNotFound();
		};

	};
};


#endif
