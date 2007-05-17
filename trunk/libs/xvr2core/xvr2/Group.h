/*
 * $Id$
 */
#ifndef __XVR2_GROUP_H__
#define __XVR2_GROUP_H__

#include<xvr2/Unix.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	/**
	 * \class Group Group.h
	 * \brief This class deals with group management and also provides means
	 * to search the system's user group database
	 */
	class Group:protected Unix{
		protected:
			/** Internal numeric group id reference member */
			int _groupid;
			/** Internal numeric group id reference member */
			//String _groupname;
			std::string *string_representation;
			/**
			 * This method will return a groupname based on a
			 * numeric group id.
			 * <b>BE CAREFULL WHEN USING THIS FUNCTION AND ALLWAYS
			 * RELEASE THE POINTER IT RETURN IN ORDER TO PREVENT
			 * MEMORY LEAKS</b>
			 */
			char *getGroupName(int gid);
		public:
			/** 
			 * This is the default constructor, it will initialize the 
			 * internal groupid and groupname to the same one as the
			 * current executing process
			 */
			Group();
			~Group();
			/** 
			 * This will create a new Group object with groupid <b>gid</b>
			 */
			Group(int gid);
			/** 
			 * This will create a new Group object with groupname
			 * <b>gname</b>
			 * \param gname Is the group name to be created
			 */
			Group(const String &gname);
			/** This will return the object's numeric group id */
			int  getGroupID();
			/** This will return the current process's group id */
			static int  getCurrentGroupID();
			/** This will return the numeric group id corresponding
			 *  to the string <b>gname</b> */
			static int  getGroupID(const String &gname);
			/** This will give the numeric effective group id */
			static int  getEffectiveGroupID();
			/** This will set the current process group id to <b>gid</b>*/
			static void setGroupID(int gid);
			/** This will set the current process group name to <b>gname</b>*/
			static void setGroupID(const String &gname);
			/** This will set the current process group to <b>grpobj</b>*/
			static void setGroupID(const Group &grpobj);
			/** This will set the current process effective group id to <b>gid</b>*/
			static void setEffectiveGroupID(int gid);
			/** This will set the current process effective group name to <b>gname</b>*/
			static void setEffectiveGroupID(const String &gname);
			/** This will set the current process effective group to <b>grpobj</b>*/
			static void setEffectiveGroupID(const Group &grpobj);
			/** This will return the corresponding groupname as a string */
			std::string toString();
	};
};

#endif
