/*
 * $Id$
 */
#include<FileException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		File::File(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2FileException);
#endif
			description = (char *)xvr2::excepFile;
		}

		FeatureNotAvailableOnPipesOrSocket::FeatureNotAvailableOnPipesOrSocket(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2FeatureNotAvailableOnPipesOrSocketException);
#endif
			description = (char *)xvr2::excepFeatureNotAvailableOnPipesOrSocket;
		}

		FileNotOpened::FileNotOpened(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2FileNotOpenedException);
#endif
			description = (char *)xvr2::excepFileNotOpened;
		}

		FileExists::FileExists(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2FileExistsException);
#endif
			description = (char *)xvr2::excepFileExists;
		}

		ThisIsADirectory::ThisIsADirectory(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ThisIsADirectoryException);
#endif
			description = (char *)xvr2::excepThisIsADirectory;
		}

		PermissionDenied::PermissionDenied(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2PermissionDeniedException);
#endif
			description = (char *)xvr2::excepPermissionDenied;
		}

		FilenameTooLong::FilenameTooLong(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2FilenameTooLongException);
#endif
			description = (char *)xvr2::excepFilenameTooLong;
		}

		FileOrDirectoryNotFound::FileOrDirectoryNotFound(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2FileOrDirectoryNotFoundException);
#endif
			description = (char *)xvr2::excepFileOrDirectoryNotFound;
		}

		ThisIsNotADirectory::ThisIsNotADirectory(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ThisIsNotADirectoryException);
#endif
			description = (char *)xvr2::excepThisIsNotADirectory;
		}

		UnableToWriteOnReadOnlyFile::UnableToWriteOnReadOnlyFile(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UnableToWriteOnReadOnlyFileException);
#endif
			description = (char *)xvr2::excepUnableToWriteOnReadOnlyFile;
		}

		UnableToWriteOnRunningExecutableFile::UnableToWriteOnRunningExecutableFile(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UnableToWriteOnRunningExecutableFileException);
#endif
			description = (char *)xvr2::excepUnableToWriteOnRunningExecutableFile;
		}

		FilenameExceedsAddressSpace::FilenameExceedsAddressSpace(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2FilenameExceedsAddressSpaceException);
#endif
			description = (char *)xvr2::excepFilenameExceedsAddressSpace;
		}

		TooManySymlinks::TooManySymlinks(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2TooManySymlinksException);
#endif
			description = (char *)xvr2::excepTooManySymlinks;
		}

		NotEnoughStorageSpace::NotEnoughStorageSpace(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NotEnoughStorageSpaceException);
#endif
			description = (char *)xvr2::excepNotEnoughStorageSpace;
		}

		NotEnoughKernelMemory::NotEnoughKernelMemory(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NotEnoughKernelMemoryException);
#endif
			description = (char *)xvr2::excepNotEnoughKernelMemory;
		}

		MaximumNumberOfOpenFilesForThisProcess::MaximumNumberOfOpenFilesForThisProcess(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2MaximumNumberOfOpenFilesForThisProcessException);
#endif
			description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisProcess;
		}

		MaximumNumberOfOpenFilesForThisSystem::MaximumNumberOfOpenFilesForThisSystem(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2MaximumNumberOfOpenFilesForThisSystemException);
#endif
			description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisSystem;
		}


		WriteWillBlock::WriteWillBlock(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2WriteWillBlockException);
#endif
			description = (char *)xvr2::excepWriteWillBlock;
		}

		FileTooBig::FileTooBig(){
#ifndef USING_GCC3
		        setClassName((char *)xvr2::_xvr2FileTooBigException);
#endif
		        description = (char *)xvr2::excepFileTooBig;
		}

		FileNotFound::FileNotFound(){
#ifndef USING_GCC3
		        setClassName((char *)xvr2::_xvr2FileNotFoundException);
#endif
		        description = (char *)xvr2::excepFileNotFound;
		}

	};
};


