/*
 * $Id$
 */
#include"config.h"
#include"Unix.h"
#include"Mutex.h"
#include"DebugConsole.h"
#include"FileException.h"
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>
#include<unistd.h>
#include<sys/utsname.h>
#if __GNUC__ < 3
#include<string.h>
#include<stdlib.h>
#else
#include<string>
#endif

#if __GNUC__ >= 3
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
#if __GNUC__ < 3
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
		buffer = new char[1024];
		getpwnam_r(username.toCharPtr(), &p1, buffer, 1024, &p2);
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
		buffer = new char[1024];
		//getpwnam_r(u->toCharPtr(), &p1, buffer, 1024, &p2);
		getgrnam_r(groupname.toCharPtr(), p1, buffer, 1024, &p2);
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
		ret = ::chown(fname.toCharPtr(), userid, (gid_t)(groupid));
		if(ret == -1){
			switch(errno){
				case EPERM:
					throw UserIDDoesNotMatch();
					break;
				case EROFS:
					throw UnableToWriteOnReadOnlyFile();
					break;
				case EFAULT:
					throw FilenameExceedsAddressSpace();
					break;
				case ENAMETOOLONG:
					throw FilenameTooLong();
					break;
				case ENOENT:
					throw FileOrDirectoryNotFound();
					break;
				case ENOMEM:
					throw NotEnoughKernelMemory();
					break;
				case ENOTDIR:
					throw ThisIsNotADirectory();
					break;
				case EACCES:
					throw PermissionDenied();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw TooManySymlinks();
					break;
#endif
				case EBADF:
					throw FileNotOpened();
					break;
				case EIO:
					throw IOException();
					break;
				default:
					throw FileException();
			};
		}
		return ret;
	}

	int Unix::chown(const String &fname, const String &owner){
		int ret;
		int userid;
		userid = Unix::getuid(owner);
		try{
			ret = Unix::chown(fname.toCharPtr(), userid, (gid_t)(-1));
		}
		catch(...){
			throw;
		}
		return ret;
	}

	int Unix::chgrp(const String &fname, int groupid){
		int ret;
		ret = ::chown(fname.toCharPtr(), (uid_t)(-1), (gid_t)(groupid));
		if(ret == -1){
			switch(errno){
				case EPERM:
					throw UserIDDoesNotMatch();
					break;
				case EROFS:
					throw UnableToWriteOnReadOnlyFile();
					break;
				case EFAULT:
					throw FilenameExceedsAddressSpace();
					break;
				case ENAMETOOLONG:
					throw FilenameTooLong();
					break;
				case ENOENT:
					throw FileOrDirectoryNotFound();
					break;
				case ENOMEM:
					throw NotEnoughKernelMemory();
					break;
				case ENOTDIR:
					throw ThisIsNotADirectory();
					break;
				case EACCES:
					throw PermissionDenied();
					break;
#ifdef USING_LINUX
				case ELOOP:
					throw TooManySymlinks();
					break;
#endif
				case EBADF:
					throw FileNotOpened();
					break;
				case EIO:
					throw IOException();
					break;
				default:
					throw FileException();
			};
		}
		return ret;
	}

	int Unix::chgrp(const String &fname, const String &groupname){
		int ret;
		int userid;
		userid = Unix::getgid(groupname);
		ret = Unix::chown(fname.toCharPtr(), userid, (gid_t)(-1));
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
		catch(Exception e1){
#ifdef USE_DEBUG
			debugConsole << "Unable to lock OSMutex while calling Unix::getKernelInfo, read more below\n" << e1.toString() << "\n";
#endif
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
		catch(Exception e1){
#ifdef USE_DEBUG
			debugConsole << "Unable to lock OSMutex while calling Unix::getKernelInfo, read more below\n" << e1.toString() << "\n";
#endif
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
