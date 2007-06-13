/*
 * $Id$
 */
#include"config.h"
#include "User.h"
#include<pwd.h>
#include<unistd.h>
#include<string>

namespace xvr2{

	char *User::_getUsername(int uid){
		struct passwd p1;
		struct passwd *p2;
		char *buffer;
		char *uname;
		buffer = new char[1024];
		getpwuid_r(uid, &p1, buffer, 1024, &p2);
		uname = new char(strlen(p1.pw_name) + 1);
		strcpy(uname, p1.pw_name);
		xvr2_delete_array(buffer);
		return uname;
	}

	User::~User(){
		delete string_representation;
	}
	User::User(){
		char *tmpptr;
		_userid = User::getCurrentUserID();
		tmpptr = _getUsername(_userid);
		//_username = tmpptr;
		string_representation = new std::string(tmpptr);
		xvr2_delete(tmpptr);
	}

	User::User(int uid){
		char *tmpptr;
		_userid = uid;
		tmpptr = _getUsername(_userid);
		//_username = tmpptr;
		string_representation = new std::string(tmpptr);
		xvr2_delete(tmpptr);
	}

	User::User(const String &uname){
		_userid = Unix::getuid(uname);
		//_username = uname.toCharPtr();
		string_representation = new std::string(uname.toCharPtr());
	}

	int User::getUserID(){
		return _userid;
	}

	int User::getCurrentUserID(){
		return Unix::getuid();
	}

	int User::getUserID(const String &uname){
		struct passwd u1;
		struct passwd *u2;
		char *buffer;
		int x_uid;
		buffer = new char[1024];
		getpwnam_r(uname.toCharPtr(), &u1, buffer, 1024, &u2);
		if(u2 == 0)
			throw UserException();
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

	std::string User::toString(){
		//return _username.toString();
		//return *string_representation;
		return std::string(string_representation->c_str());
	}
};
