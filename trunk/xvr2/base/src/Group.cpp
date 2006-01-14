/*
 * $Id$
 */
#ifndef __XVR2_UNIX_GROUP_H__
#define __XVR2_UNIX_GROUP_H__
#include<xvr2/Group.h>
#include<sys/types.h>
#include<unistd.h>
#include<grp.h>

#define DONT_HAVE_REENTRANT_GETGRGID

#ifdef DONT_HAVE_REENTRANT_GETGRGID
#include<Mutex.h>
#include<string>
#endif

#ifndef GROUP_INFO_BUFFER_SIZE
#define GROUP_INFO_BUFFER_SIZE 256
#endif

#include<errno.h>
#ifdef GCC_REVISION4
#include<cerrno>
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
				throw Exception::BufferTooSmall();
			}
			else{
				if(errno == ENOMEM){
					throw Exception::Memory();
				}
			}
			if(g2 == 0x0){
				throw Exception::Memory();
			}
		}
		g_ptr = strdup(g2->gr_name);
		xvr2_delete_array(buffer);
		return g_ptr;
	}

	Group::Group(){
		char *tmpptr;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Group);
#endif
		_groupid = Group::getCurrentGroupID();
		tmpptr = getGroupName(_groupid);
		_groupname = tmpptr;
		free(tmpptr);
	}

	Group::Group(int gid){
		char *tmpptr;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Group);
#endif
		_groupid = gid;
		tmpptr = getGroupName(gid);
		_groupname = tmpptr;
		free(tmpptr);
	}

	Group::Group(const String &gname){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Group);
#endif
		_groupname = gname;
		_groupid = Unix::getgid(gname);
	}

	const std::string &Group::toString(){
		return _groupname.toString();
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

#endif
