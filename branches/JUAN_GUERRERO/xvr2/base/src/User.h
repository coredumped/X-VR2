/*
 * $Id$
 */
#ifndef __XVR2_USER_H__
#define __XVR2_USER_H__

#include<Unix.h>
#include<UserException.h>

namespace xvr2{
	/**
	 * This class deals with user management and numeric id setup on
	 * on running processes
	 */
	class User:protected Unix{
		protected:
			/** This member stores the numeric user id */
			int _userid;
			/** This member stores the username as a string*/
			String _username;
			/** This will translate a numeric user id into a null terminated character array */
			static char *_getUsername(int uid);
		public:
			/** 
			 * This is the default constructor, it will initialize the 
			 * internal userid and username to the same one as the
			 * current executing process
			 */
			User();
			/** 
			 * This will create a new User object with userid <b>uid</b>
			 */
			User(int uid);
			/** 
			 * This will create a new User object with username
			 * <b>uname</b>
			 */
			User(const String &uname);
			/** This will return the object's numeric user id */
			int getUserID();
			/** This will return the current process's user id */
			static int getCurrentUserID();
			/** This will return the numeric user id corresponding
			 *  to the string <b>uname</b> */
			static int getUserID(const String &uname);
			/** This will give the numeric effective user id */
			static int getEffectiveUserID();

			/** This will set the current process user id to <b>uid</b>*/
			static void setUserID(int uid);
			/** This will set the current process user id to <b>uname</b>*/
			static void setUserID(const String &uname);
			/** This will set the current process user id to <b>usrobj</b>*/
			static void setUserID(const User &usrobj);

			/** This will set the current process effective user id to <b>uid</b>*/
			static void setEffectiveUserID(int uid);
			/** This will set the current process effective user id to <b>uname</b>*/
			static void setEffectiveUserID(const String &uname);
			/** This will set the current process effective user id to <b>usrobj</b>*/
			static void setEffectiveUserID(const User &usrobj);

			const String &toString();
	};
};

#endif
