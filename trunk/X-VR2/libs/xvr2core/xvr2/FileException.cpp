/*
 * $Id$
 */
#include"config.h"
#include"xvr2config.h"
#include"FileException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		FileException::FileException(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2FileException);
#endif
			description = (char *)xvr2::excepFile;
		}

		FeatureNotAvailableOnPipesOrSocket::FeatureNotAvailableOnPipesOrSocket(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2FeatureNotAvailableOnPipesOrSocketException);
#endif
			description = (char *)xvr2::excepFeatureNotAvailableOnPipesOrSocket;
		}

		FileNotOpened::FileNotOpened(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2FileNotOpenedException);
#endif
			description = (char *)xvr2::excepFileNotOpened;
		}

		FileExists::FileExists(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2FileExistsException);
#endif
			description = (char *)xvr2::excepFileExists;
		}

		ThisIsADirectory::ThisIsADirectory(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2ThisIsADirectoryException);
#endif
			description = (char *)xvr2::excepThisIsADirectory;
		}

		PermissionDenied::PermissionDenied(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2PermissionDeniedException);
#endif
			description = (char *)xvr2::excepPermissionDenied;
		}

		FilenameTooLong::FilenameTooLong(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2FilenameTooLongException);
#endif
			description = (char *)xvr2::excepFilenameTooLong;
		}

		FileOrDirectoryNotFound::FileOrDirectoryNotFound(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2FileOrDirectoryNotFoundException);
#endif
			description = (char *)xvr2::excepFileOrDirectoryNotFound;
		}

		ThisIsNotADirectory::ThisIsNotADirectory(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2ThisIsNotADirectoryException);
#endif
			description = (char *)xvr2::excepThisIsNotADirectory;
		}

		UnableToWriteOnReadOnlyFile::UnableToWriteOnReadOnlyFile(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2UnableToWriteOnReadOnlyFileException);
#endif
			description = (char *)xvr2::excepUnableToWriteOnReadOnlyFile;
		}

		UnableToWriteOnRunningExecutableFile::UnableToWriteOnRunningExecutableFile(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2UnableToWriteOnRunningExecutableFileException);
#endif
			description = (char *)xvr2::excepUnableToWriteOnRunningExecutableFile;
		}

		FilenameExceedsAddressSpace::FilenameExceedsAddressSpace(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2FilenameExceedsAddressSpaceException);
#endif
			description = (char *)xvr2::excepFilenameExceedsAddressSpace;
		}

		TooManySymlinks::TooManySymlinks(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2TooManySymlinksException);
#endif
			description = (char *)xvr2::excepTooManySymlinks;
		}

		NotEnoughStorageSpace::NotEnoughStorageSpace(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2NotEnoughStorageSpaceException);
#endif
			description = (char *)xvr2::excepNotEnoughStorageSpace;
		}

		NotEnoughKernelMemory::NotEnoughKernelMemory(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2NotEnoughKernelMemoryException);
#endif
			description = (char *)xvr2::excepNotEnoughKernelMemory;
		}

		MaximumNumberOfOpenFilesForThisProcess::MaximumNumberOfOpenFilesForThisProcess(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2MaximumNumberOfOpenFilesForThisProcessException);
#endif
			description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisProcess;
		}

		MaximumNumberOfOpenFilesForThisSystem::MaximumNumberOfOpenFilesForThisSystem(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2MaximumNumberOfOpenFilesForThisSystemException);
#endif
			description = (char *)xvr2::excepMaximumNumberOfOpenFilesForThisSystem;
		}


		WriteWillBlock::WriteWillBlock(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2WriteWillBlockException);
#endif
			description = (char *)xvr2::excepWriteWillBlock;
		}

		FileTooBig::FileTooBig(){
#if __GNUC__ < 3
		        setClassName((char *)xvr2::_xvr2FileTooBigException);
#endif
		        description = (char *)xvr2::excepFileTooBig;
		}

		FileNotFound::FileNotFound(){
#if __GNUC__ < 3
		        setClassName((char *)xvr2::_xvr2FileNotFoundException);
#endif
		        description = (char *)xvr2::excepFileNotFound;
		}

	};
};


