/*
 * $Id$
 */
#include<Unix.h>
#include<Mutex.h>
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>
#include<sys/utsname.h>
#ifndef USING_GCC3
#include<string.h>
#include<stdlib.h>
#else
#include<string>
#endif

#ifdef GCC_REVISION4
#include<cerrno>
#else
#include<errno.h>
#endif


namespace xvr2{

	void Unix::destroyAll(){
		if(sysname != 0)
			free(sysname);
		if(nodename != 0)
			free(nodename);
		if(release != 0)
			free(release);
		if(k_version != 0)
			free(k_version);
		if(machine != 0)
			free(machine);
		sysname = 0;
		nodename = 0;
		release = 0;
		k_version = 0;
		machine = 0;
	}

	Unix::Unix(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Unix);
#endif
		sysname = 0;
		nodename = 0;
		release = 0;
		k_version = 0;
		machine = 0;
		//getKernelInfo();
	}

	Unix::~Unix(){
		destroyAll();
	}

	int Unix::getuid(const String &username){
		int userid;
		struct passwd p1;
		struct passwd *p2;
		char *buffer;
		String *u;
		buffer = new char[1024];
		u = (String *)&username;
		getpwnam_r(u->toCharPtr(), &p1, buffer, 1024, &p2);
		userid = p1.pw_uid;
		delete[] buffer;
		return userid;
	}

	int Unix::getuid(){
		return ::getuid();
	}

	int Unix::getgid(const String &groupname){
		int groupid;
		struct group *p1;
		struct group *p2;
		char *buffer;
		String *u;
		buffer = new char[1024];
		u = (String *)&groupname;
		//getpwnam_r(u->toCharPtr(), &p1, buffer, 1024, &p2);
		getgrnam_r(u->toCharPtr(), p1, buffer, 1024, &p2);
		if(p2 == 0){
			//TODO: remember to code whatever goes here
		}
		groupid = p1->gr_gid;
		delete[] buffer;
		return groupid;
	}

	int Unix::getgid(){
		return ::getgid();
	}

	int Unix::chown(const String &fname, int userid, int groupid){
		int ret;
		String *c;
		c = (String *)&fname;
		ret = ::chown(c->toCharPtr(), userid, (gid_t)(groupid));
		if(ret == -1){
			switch(errno){
				case EPERM:
					throw Exception::UserIDDoesNotMatch();
					break;
				case EROFS:
					throw Exception::UnableToWriteOnReadOnlyFile();
					break;
				case EFAULT:
					throw Exception::FilenameExceedsAddressSpace();
					break;
				case ENAMETOOLONG:
					throw Exception::FilenameTooLong();
					break;
				case ENOENT:
					throw Exception::FileOrDirectoryNotFound();
					break;
				case ENOMEM:
					throw Exception::NotEnoughKernelMemory();
					break;
				case ENOTDIR:
					throw Exception::ThisIsNotADirectory();
					break;
				case EACCES:
					throw Exception::PermissionDenied();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw Exception::TooManySymlinks();
					break;
#endif
				case EBADF:
					throw Exception::FileNotOpened();
					break;
				case EIO:
					throw Exception::IO();
					break;
				default:
					throw Exception::File();
			};
		}
		return ret;
	}

	int Unix::chown(const String &fname, const String &owner){
		int ret;
		int userid;
		String *c;
		c = (String *)&fname;
		userid = Unix::getuid(owner);
		try{
			ret = Unix::chown(c->toCharPtr(), userid, (gid_t)(-1));
		}
		catch(...){
			throw;
		}
		return ret;
	}

	int Unix::chgrp(const String &fname, int groupid){
		int ret;
		String *c;
		c = (String *)&fname;
		ret = ::chown(c->toCharPtr(), (uid_t)(-1), (gid_t)(groupid));
		if(ret == -1){
			switch(errno){
				case EPERM:
					throw Exception::UserIDDoesNotMatch();
					break;
				case EROFS:
					throw Exception::UnableToWriteOnReadOnlyFile();
					break;
				case EFAULT:
					throw Exception::FilenameExceedsAddressSpace();
					break;
				case ENAMETOOLONG:
					throw Exception::FilenameTooLong();
					break;
				case ENOENT:
					throw Exception::FileOrDirectoryNotFound();
					break;
				case ENOMEM:
					throw Exception::NotEnoughKernelMemory();
					break;
				case ENOTDIR:
					throw Exception::ThisIsNotADirectory();
					break;
				case EACCES:
					throw Exception::PermissionDenied();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw Exception::TooManySymlinks();
					break;
#endif
				case EBADF:
					throw Exception::FileNotOpened();
					break;
				case EIO:
					throw Exception::IO();
					break;
				default:
					throw Exception::File();
			};
		}
		return ret;
	}

	int Unix::chgrp(const String &fname, const String &groupname){
		int ret;
		int userid;
		String *c;
		c = (String *)&fname;
		userid = Unix::getgid(groupname);
		ret = Unix::chown(c->toCharPtr(), userid, (gid_t)(-1));
		return ret;
	}

	void Unix::getKernelInfo(){
		//
		// TODO
		// Verify that the uname() system call is thread safe
		//
		struct utsname data;
		try{
			OSMutex.lock();
		}
		catch(Exception::Exception e1){
			std::cerr << "Unable to lock OSMutex while calling Unix::getKernelInfo, read more below\n" << e1.toString() << std::endl;
		}
		uname(&data);
		sysname   = strdup(data.sysname);
		nodename  = strdup(data.nodename);
		release   = strdup(data.release);
		k_version = strdup(data.version);
		machine   = strdup(data.machine);
		try{
			OSMutex.unlock();
		}
		catch(Exception::Exception e1){
			std::cerr << "Unable to unlock OSMutex while calling Unix::getKernelInfo, read more below\n" << e1.toString() << std::endl;
		}
	}

	const char *Unix::getUnixName(){
		if(sysname == 0)
			getKernelInfo();
		return sysname;
	};

	const char *Unix::getNodeName(){
		if(nodename == 0)
			getKernelInfo();
		return nodename;
	};

	const char *Unix::getKernelRelease(){
		if(release == 0)
			getKernelInfo();
		return release;
	};

	const char *Unix::getKernelReleaseVersion(){
		if(k_version == 0)
			getKernelInfo();
		return k_version;
	};

	const char *Unix::getHostMachine(){
		if(machine == 0)
			getKernelInfo();
		return machine;
	};

};
