/*
 * $Id$
 */
#include<MessageStrings.h>
#include<BaseFile.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

namespace xvr2{

	BaseFile::BaseFile(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2BaseFile);
#endif
		filename.assign(constDEVNULL);
		filemode = -1;
		_opened = false;
	}

	BaseFile::BaseFile(const char *fname){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2BaseFile);
#endif
		filename.assign(fname);
		filemode = -1;
		_opened = false;
	}

	BaseFile::BaseFile(const String &fname){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2BaseFile);
#endif
		filename = fname;
		filemode = -1;
		_opened = false;
	}

	void BaseFile::setFilename(const char *fname){
		filename.assign(fname);
	}

	void BaseFile::setFilename(const String &fname){
		filename = fname;
	}

	void BaseFile::open(const String &fname, BaseFile::FileOpenMode mode){
		filename = fname;
		open(mode);
	}

	void BaseFile::open(const char *fname, BaseFile::FileOpenMode mode){
		setFilename(fname);
		open(mode);
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
					throw Exception::FileExists();
					break;
				case EISDIR:
					throw Exception::ThisIsADirectory();
					break;
				case EACCES:
					throw Exception::PermissionDenied();
					break;
				case ENAMETOOLONG:
					throw Exception::FilenameTooLong();
					break;
				case ENOENT:
					throw Exception::FileOrDirectoryNotFound();
					break;
				case ENOTDIR:
					throw Exception::ThisIsNotADirectory();
					break;
				case ENXIO:
					throw Exception::DeviceOrFIFONotFound();
					break;
				case ENODEV:
					throw Exception::DeviceNotFound();
					break;
				case EROFS:
					throw Exception::UnableToWriteOnReadOnlyFile();
					break;
#ifdef USING_LINUX
				case ETXTBSY:
					throw Exception::UnableToWriteOnRunningExecutableFile();
					break;
#endif
				case EFAULT:
					throw Exception::FilenameExceedsAddressSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw Exception::TooManySymlinks();
					break;
#endif
				case ENOSPC:
					throw Exception::NotEnoughStorageSpace();
					break;
				case ENOMEM:
					throw Exception::NotEnoughKernelMemory();
					break;
				case EMFILE:
					throw Exception::MaximumNumberOfOpenFilesForThisProcess();
					break;
				case ENFILE:
					throw Exception::MaximumNumberOfOpenFilesForThisSystem();
					break;
				default:
					throw Exception::File();
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
						throw Exception::FileNotOpened();
						break;
					case ESPIPE:
						throw Exception::FeatureNotAvailableOnPipesOrSocket();
						break;
					case EINVAL:
						throw Exception::InvalidParameter();
						break;
					default:
						throw Exception::File();
				}
			}
		}
		else{
			throw Exception::FileNotOpened();
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
					throw Exception::InvalidParameter();
			}
			if(((int)s_siz) == -1){
				switch(errno){
					case EBADF:
						throw Exception::FileNotOpened();
						break;
					case ESPIPE:
						throw Exception::FeatureNotAvailableOnPipesOrSocket();
						break;
					case EINVAL:
						throw Exception::InvalidParameter();
						break;
					default:
						throw Exception::File();
				}
			}
		}
		else{
			throw Exception::FileNotOpened();
		}
		return s_siz;
	}

	void BaseFile::flush(){
		if(isOpen()){
			sync();
		}
		else{
			throw Exception::FileNotOpened();
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
					throw Exception::PermissionDenied();
					break;
				case ENAMETOOLONG:
					throw Exception::FilenameTooLong();
					break;
				case ENOENT:
					throw Exception::FileOrDirectoryNotFound();
					break;
				case ENOTDIR:
					throw Exception::ThisIsNotADirectory();
					break;
				case EFAULT:
					throw Exception::FilenameExceedsAddressSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw Exception::TooManySymlinks();
					break;
#endif
				case ENOMEM:
					throw Exception::NotEnoughKernelMemory();
					break;
				default:
					throw Exception::File();
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
					throw Exception::UserIDDoesNotMatch();
					break;
				case EBADF:
					throw Exception::FileNotOpened();
					break;
				case EIO:
					throw Exception::IO();
					break;
				case EROFS:
					throw Exception::UnableToWriteOnReadOnlyFile();
					break;
				case EACCES:
					throw Exception::PermissionDenied();
					break;
				case ENAMETOOLONG:
					throw Exception::FilenameTooLong();
					break;
				case ENOENT:
					throw Exception::FileOrDirectoryNotFound();
					break;
				case ENOTDIR:
					throw Exception::ThisIsNotADirectory();
					break;
				case EFAULT:
					throw Exception::FilenameExceedsAddressSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw Exception::TooManySymlinks();
					break;
#endif
				case ENOMEM:
					throw Exception::NotEnoughKernelMemory();
					break;
				default:
					throw Exception::File();
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
					throw Exception::FileNotOpened();
					break;
				case EINVAL:
					throw Exception::InvalidParameter();
					break;
				case EFAULT:
					throw Exception::FilenameExceedsAddressSpace();
					break;
				case EFBIG:
					throw Exception::FileTooBig();
					break;
				case EPIPE:
					throw Exception::BrokenPipe();
					break;
				case EAGAIN:
					throw Exception::WriteWillBlock();
					break;
				case EINTR:
					throw Exception::InterruptedSystemCall();
					break;
				case EIO:
					throw Exception::IO();
					break;
				case ENOSPC:
					throw Exception::NotEnoughStorageSpace();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw Exception::TooManySymlinks();
					break;
#endif
				default:
					throw Exception::File();
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
					throw Exception::FileNotOpened();
					break;
				case EINVAL:
					throw Exception::InvalidParameter();
					break;
				case EFAULT:
					throw Exception::FilenameExceedsAddressSpace();
					break;
				case EPIPE:
					throw Exception::BrokenPipe();
					break;
				case EAGAIN:
					throw Exception::WriteWillBlock();
					break;
				case EINTR:
					throw Exception::InterruptedSystemCall();
					break;
				case EIO:
					throw Exception::IO();
					break;
				case EISDIR:
					throw Exception::ThisIsADirectory();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw Exception::TooManySymlinks();
					break;
#endif
				default:
					throw Exception::File();
			}
			return 0;
		}
		return siz;
	}

	const String &BaseFile::getFilename(){
		return filename;
	}
};
