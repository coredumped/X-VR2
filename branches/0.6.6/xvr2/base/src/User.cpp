/*
 * $Id$
 */
#include<User.h>
#include<pwd.h>
#include<unistd.h>
#include<string>

namespace xvr2{

	char *User::_getUsername(int uid){
		struct passwd *p1;
		struct passwd *p2;
		char *buffer;
		char *uname;
		buffer = new char[1024];
		getpwuid_r(uid, p1, buffer, 1024, &p2);
		uname = new char(strlen(p1->pw_name) + 1);
		strcpy(uname, p1->pw_name);
		xvr2_delete_array(buffer);
		return uname;
	}

	User::User(){
		char *tmpptr;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2User);
#endif
		_userid = User::getCurrentUserID();
		tmpptr = _getUsername(_userid);
		_username = tmpptr;
		xvr2_delete(tmpptr);
	}

	User::User(int uid){
		char *tmpptr;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2User);
#endif
		_userid = uid;
		tmpptr = _getUsername(_userid);
		_username = tmpptr;
		xvr2_delete(tmpptr);
	}

	User::User(const String &uname){
		String *u;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2User);
#endif
		u = (String *)&uname;
		_userid = Unix::getuid(uname);
		_username = u->toCharPtr();
	}

	int User::getUserID(){
		return _userid;
	}

	int User::getCurrentUserID(){
		return Unix::getuid();
	}

	int User::getUserID(const String &uname){
		struct passwd *u1;
		struct passwd *u2;
		String *u;
		char *buffer;
		int x_uid;
		u = (String *)&uname;
		buffer = new char[1024];
		getpwnam_r(u->toCharPtr(), u1, buffer, 1024, &u2);
		if(u2 == 0)
			throw Exception::User();
		x_uid = u2->pw_uid;
		xvr2_delete_array(buffer);
		return x_uid;
	}

	int User::getEffectiveUserID(){
		return ::geteuid();
	}

	void User::setUserID(int uid){
		::setuid(uid);
	}

	void User::setUserID(const String &uname){
		setUserID(getUserID(uname));
	}

	void User::setUserID(const User &usrobj){
		User *u;
		u = (User *)&usrobj;
		setUserID(u->getUserID());
	}







	void User::setEffectiveUserID(int uid){
		::seteuid(uid);
	}

	void User::setEffectiveUserID(const String &uname){
		setEffectiveUserID(getUserID(uname));
	}

	void User::setEffectiveUserID(const User &usrobj){
		User *u;
		u = (User *)&usrobj;
		setEffectiveUserID(u->getUserID());
	}
};