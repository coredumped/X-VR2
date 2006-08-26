/*
 * $Id$
 */
#include"config.h"
#include"MessageStrings.h"
#include"BaseFile.h"
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

namespace xvr2{

	BaseFile::BaseFile(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2BaseFile);
#endif
		filename.assign(constDEVNULL);
		filemode = -1;
		_opened = false;
	}

	BaseFile::BaseFile(const char *fname){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2BaseFile);
#endif
		filename.assign(fname);
		filemode = -1;
		_opened = false;
	}

	BaseFile::BaseFile(const String &fname){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2BaseFile);
#endif
		filename.assign(fname.toCharPtr());
		filemode = -1;
		_opened = false;
	}

	void BaseFile::setFilename(const char *fname){
		filename.assign(fname);
	}

	void BaseFile::setFilename(const String &fname){
		filename.assign(fname.toCharPtr());
	}

	void BaseFile::open(const String &fname, BaseFile::FileOpenMode mode){
		filename.assign(fname.toCharPtr());
		BaseFile::open(mode);
	}

	void BaseFile::open(const char *fname, BaseFile::FileOpenMode mode){
		setFilename(fname);
		BaseFile::open(mode);
	}

	//This method must be overriden if u want to use higher level file handling
	void BaseFile::open(BaseFile::FileOpenMode mode){
		switch(mode){
			case READ_ONLY:
				handler = ::open(filename.toCharPtr(), O_RDONLY);
				break;
			case WRITE_ONLY:
				handler = ::open(filename.toCharPtr(), O_CREAT|O_TRUNC|O_WRONLY);
				break;
			case READ_WRITE:
				handler = ::open(filename.toCharPtr(), O_CREAT|O_TRUNC|O_RDWR);
				break;
			case APPEND:
				handler = ::open(filename.toCharPtr(), O_CREAT|O_TRUNC|O_APPEND);
				break;
			default:
				handler = ::open(filename.toCharPtr(), O_CREAT|O_TRUNC|O_RDONLY);
		}
		if(handler == -1){
			//Something bad happened
			switch(errno){
				case EEXIST:
					throw FileExists();
					break;
				case EISDIR:
					throw ThisIsADirectory();
					break;
				case EACCES:
					throw PermissionDenied();
					break;
				case ENAMETOOLONG:
					throw FilenameTooLong();
					break;
				case ENOENT:
					throw FileOrDirectoryNotFound();
					break;
				case ENOTDIR:
					throw ThisIsNotADirectory();
					break;
				case ENXIO:
					throw DeviceOrFIFONotFound();
					break;
				case ENODEV:
					throw DeviceNotFound();
					break;
				case EROFS:
					throw UnableToWriteOnReadOnlyFile();
					break;
#ifdef USING_LINUX
				case ETXTBSY:
					throw UnableToWriteOnRunningExecutableFile();
					break;
#endif
				case EFAULT:
					throw FilenameExceedsAddressSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw TooManySymlinks();
					break;
#endif
				case ENOSPC:
					throw NotEnoughStorageSpace();
					break;
				case ENOMEM:
					throw NotEnoughKernelMemory();
					break;
				case EMFILE:
					throw MaximumNumberOfOpenFilesForThisProcess();
					break;
				case ENFILE:
					throw MaximumNumberOfOpenFilesForThisSystem();
					break;
				default:
					throw FileException();
			}
		}
		else{
			filemode = mode;
			_opened = true;
		}
	}


	void BaseFile::close(){
		if(isOpen()){
			::close(handler);
		}
	}

	UInt32 BaseFile::getOffset(){
		UInt32 s_siz = 0;
		if(isOpen()){
			s_siz = lseek(handler, 0, SEEK_CUR);
			if(((int)s_siz) == -1){
				switch(errno){
					case EBADF:
						throw FileNotOpened();
						break;
					case ESPIPE:
						throw FeatureNotAvailableOnPipesOrSocket();
						break;
					case EINVAL:
						throw InvalidParameter();
						break;
					default:
						throw FileException();
				}
			}
		}
		else{
			throw FileNotOpened();
		}
		return s_siz;
	}

	UInt32 BaseFile::setOffset(UInt32 off, OffsetStartingPoint from){
		UInt32 s_siz;
		if(isOpen()){
			switch(from){
				case FROM_THE_BEGINING:
					s_siz = lseek(handler, off, SEEK_SET);
					break;
				case FROM_CURRENT_POSITION:
					s_siz = lseek(handler, off, SEEK_CUR);
					break;
				case FROM_THE_END:
					s_siz = lseek(handler, off, SEEK_END);
					break;
				default:
					throw InvalidParameter();
			}
			if(((int)s_siz) == -1){
				switch(errno){
					case EBADF:
						throw FileNotOpened();
						break;
					case ESPIPE:
						throw FeatureNotAvailableOnPipesOrSocket();
						break;
					case EINVAL:
						throw InvalidParameter();
						break;
					default:
						throw FileException();
				}
			}
		}
		else{
			throw FileNotOpened();
		}
		return s_siz;
	}

	void BaseFile::flush(){
		if(isOpen()){
			sync();
		}
		else{
			throw FileNotOpened();
		}
	}

	UInt32 BaseFile::getSize(){
		struct stat s;
		int ret;
		if(isOpen()){
			ret = fstat(handler, &s);
		}
		else{
			ret = stat(filename.toCharPtr(), &s);
		}
		if(ret == -1){
			//Something bad happened
			switch(errno){
				case EACCES:
					throw PermissionDenied();
					break;
				case ENAMETOOLONG:
					throw FilenameTooLong();
					break;
				case ENOENT:
					throw FileOrDirectoryNotFound();
					break;
				case ENOTDIR:
					throw ThisIsNotADirectory();
					break;
				case EFAULT:
					throw FilenameExceedsAddressSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw TooManySymlinks();
					break;
#endif
				case ENOMEM:
					throw NotEnoughKernelMemory();
					break;
				default:
					throw FileException();
			}
		}
		return s.st_size;
	}


	int BaseFile::chmod(int perms){
		int ret;
		if(isOpen()){
			ret = ::fchmod(handler, perms);
		}
		else{
			ret = ::chmod(filename.toCharPtr(), perms);
		}
		if(ret == -1){
			//Something bad happened
			switch(errno){
				case EPERM:
					throw UserIDDoesNotMatch();
					break;
				case EBADF:
					throw FileNotOpened();
					break;
				case EIO:
					throw IOException();
					break;
				case EROFS:
					throw UnableToWriteOnReadOnlyFile();
					break;
				case EACCES:
					throw PermissionDenied();
					break;
				case ENAMETOOLONG:
					throw FilenameTooLong();
					break;
				case ENOENT:
					throw FileOrDirectoryNotFound();
					break;
				case ENOTDIR:
					throw ThisIsNotADirectory();
					break;
				case EFAULT:
					throw FilenameExceedsAddressSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw TooManySymlinks();
					break;
#endif
				case ENOMEM:
					throw NotEnoughKernelMemory();
					break;
				default:
					throw FileException();
			}
		}
		return ret;
	}

	UInt32 BaseFile::write(const char *buffer){
		return BaseFile::write(buffer, strlen(buffer));
	}

	UInt32 BaseFile::write(const void *buffer, UInt32 size){
		ssize_t siz;
		siz = ::write(handler, buffer, size);
		if(siz == -1){
			//Something bad happened
			switch(errno){
				case EBADF:
					throw FileNotOpened();
					break;
				case EINVAL:
					throw InvalidParameter();
					break;
				case EFAULT:
					throw FilenameExceedsAddressSpace();
					break;
				case EFBIG:
					throw FileTooBig();
					break;
				case EPIPE:
					throw BrokenPipe();
					break;
				case EAGAIN:
					throw WriteWillBlock();
					break;
				case EINTR:
					throw InterruptedSystemCall();
					break;
				case EIO:
					throw IOException();
					break;
				case ENOSPC:
					throw NotEnoughStorageSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw TooManySymlinks();
					break;
#endif
				default:
					throw FileException();
			}
			return 0;
		}
		return siz;
	}

	UInt32 BaseFile::read(void *buffer, UInt32 size){
		ssize_t siz;
		siz = ::read(handler, buffer, size);
		if(siz == -1){
			//Something bad happened
			switch(errno){
				case EBADF:
					throw FileNotOpened();
					break;
				case EINVAL:
					throw InvalidParameter();
					break;
				case EFAULT:
					throw FilenameExceedsAddressSpace();
					break;
				case EPIPE:
					throw BrokenPipe();
					break;
				case EAGAIN:
					throw WriteWillBlock();
					break;
				case EINTR:
					throw InterruptedSystemCall();
					break;
				case EIO:
					throw IOException();
					break;
				case EISDIR:
					throw ThisIsADirectory();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw TooManySymlinks();
					break;
#endif
				default:
					throw FileException();
			}
			return 0;
		}
		return siz;
	}

	const String &BaseFile::getFilename(){
		return filename;
	}
};
