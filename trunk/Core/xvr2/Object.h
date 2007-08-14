/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_OBJECT_H__
#define __XVR2_OBJECT_H__
#include<xvr2/xvr2config.h>
#include<xvr2/DataTypes.h>
#include<xvr2/__Destruct.h>
#include<string>
#include<ostream>

namespace xvr2{
	/** \class Object Object.h <xvr2/Object.h> 
	 * This one is the most primitive of all the classes, the first ancestor.
	 * All X-VR2 classes are derived from this guy.  */
	class Object{
		private:
		protected:
		public:
			/** Default constructor, it does nothing. */
			Object();
			/**
			 * Returns the name of the current class
			 */
			const char *getClassName();
			virtual ~Object();
			/**
			 * Will print a debug message to the screen */
			static void debugmsg(Object *obj, const char *msg, int linenumber = __LINE__, const char *srcfile = __FILE__);
			static void debugmsgln(Object *obj, const char *msg, int linenumber = __LINE__, const char *srcfile = __FILE__);
			virtual std::string toString();
			friend std::ostream& operator<<(std::ostream& stream, const Object &s);
	};

};
#endif
