/*
 * $Id$
 */
#include"config.h"
#include"Group.h"
#include<sys/types.h>
#include<unistd.h>
#include<grp.h>

//#define DONT_HAVE_REENTRANT_GETGRGID

#ifdef DONT_HAVE_REENTRANT_GETGRGID
#include<Mutex.h>
#include<string>
#endif

#ifndef GROUP_INFO_BUFFER_SIZE
#define GROUP_INFO_BUFFER_SIZE 256
#endif

#if __GNUC__ >= 3
#include<cerrno>
#else
#include<errno.h>
#endif

#if ((__GLIBC__ == 2) && (__GLIBC_MINOR__ > 7))
#include<cstring>
#include<cstdlib>
#endif
namespace xvr2{

#ifdef DONT_HAVE_REENTRANT_GETGRGID
/* Please define here a thread safe version of getgrgid for those Unix OSes
 * and/or c library functions that do not have a getgrgid_t function */
	Mutex __grp_shrd;
	int my_getgrgid_r(gid_t gid, struct group *RESULT_BUF, char *BUFFER, size_t BUFLEN, struct group **RESULT){
		struct group *g;
		RESULT_BUF = (struct group *)BUFFER;
		__grp_shrd.lock();
		g = getgrgid(gid);
		memcpy(RESULT_BUF, g, BUFLEN);
		*RESULT = RESULT_BUF;
		__grp_shrd.unlock();
		return 0;
	}
#endif

	char *Group::getGroupName(int gid){
		struct group *g;
		struct group *g2;
		char *buffer;
		char *g_ptr;
		int ret;
		buffer = new char[GROUP_INFO_BUFFER_SIZE];
#ifdef DONT_HAVE_REENTRANT_GETGRGID
		ret = my_getgrgid_r(gid, g, buffer, GROUP_INFO_BUFFER_SIZE, &g2);
#else
		ret = getgrgid_r(gid, g, buffer, GROUP_INFO_BUFFER_SIZE, &g2);
#endif
		if(ret != 0){
			if(errno == ERANGE){
				throw BufferTooSmall();
			}
			else{
				if(errno == ENOMEM){
					throw MemoryException();
				}
			}
			if(g2 == 0x0){
				throw MemoryException();
			}
		}
		g_ptr = strdup(g2->gr_name);
		xvr2_delete_array(buffer);
		return g_ptr;
	}

	Group::~Group(){
		delete string_representation;
	}
	Group::Group(){
		char *tmpptr;
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Group);
#endif
		_groupid = Group::getCurrentGroupID();
		tmpptr = getGroupName(_groupid);
		//_groupname = tmpptr;
		string_representation = new std::string(tmpptr);
		free(tmpptr);
	}

	Group::Group(int gid){
		char *tmpptr;
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Group);
#endif
		_groupid = gid;
		tmpptr = getGroupName(gid);
		//_groupname = tmpptr;
		string_representation = new std::string(tmpptr);
		free(tmpptr);
	}

	Group::Group(const String &gname){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Group);
#endif
		//_groupname = gname;
		string_representation = new std::string(gname.toCharPtr());
		_groupid = Unix::getgid(gname);
	}

	std::string Group::toString(){
		//return _groupname.toString();
		//return *string_representation;
		return std::string(string_representation->c_str());
	}

	int Group::getGroupID(){
		return _groupid;
	}

	int Group::getCurrentGroupID(){
		return Unix::getgid();
	}

	int Group::getGroupID(const String &gname){
		return Unix::getgid(gname);
	}

	int Group::getEffectiveGroupID(){
		return ::getegid();
	}

	void Group::setGroupID(int gid){
		::setgid(gid);
	}
	
	void Group::setGroupID(const String &gname){
		setGroupID(Unix::getgid(gname));
	}

	void Group::setGroupID(const Group &grpobj){
		Group *g;
		g = (Group *)&grpobj;
		setGroupID(g->getGroupID());
	}

	void Group::setEffectiveGroupID(int gid){
		::setegid(gid);
	}
	
	void Group::setEffectiveGroupID(const String &gname){
		setEffectiveGroupID(Unix::getgid(gname));
	}

	void Group::setEffectiveGroupID(const Group &grpobj){
		Group *g;
		g = (Group *)&grpobj;
		setEffectiveGroupID(g->getGroupID());
	}
};
