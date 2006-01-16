/*
 $Id$
 
 Here we define a parent class, THE OBJECT

 */
#ifndef __XVR2_OBJECT_H__
#define __XVR2_OBJECT_H__
#include<xvr2config.h>
#include<xvr2/_xvr2ClassNames.h>
#include<xvr2/DataTypes.h>
#include<xvr2/__Destruct.h>
#include<string>
#include<ostream>

namespace xvr2{
	/**
	 * This one is the most primitive of all the classes, the first ancestor
	 */
	class Object{
		private:
			/**
			 * Stores the name of the current class
			 */
#if __GNUC__ < 3
			char *__cls_name;
#endif
		protected:
			/**
			 * Stores a string representation of the current instantiated
			 * object */
			std::string *string_representation;
			/**
			 * Call this method when you need to set the name of the class you're
			 * creating, typically in it's constructor, remember that you must set
			 * the classname for every class you create, that way you can have more
			 * information while debugging
			 */
#if __GNUC__ < 3
			void setClassName(const char *n);
#else
			/* Under GCC 3 this is just a placebo */
			void setClassName(const char *){;}
#endif
			/**
			 * Default constructor, it only sets is own classnamw to <b>Object</b>
			 */
			Object();
		public:
			/**
			 * Returns the name of the current class
			 */
			const char *getClassName();
#if __GNUC__ < 3
			/**
			 * This constructor sets the name of the current class to <b>n</b>
			 */
			Object(const char *n){
				setClassName(n);
				string_representation = 0;
			}
#endif
			virtual ~Object();
			/**
			 * Will print a debug message to the screen */
			static void debugmsg(Object *obj, const char *msg);
			static void debugmsgln(Object *obj, const char *msg);
			virtual const std::string &toString();
			friend std::ostream& operator<<(std::ostream& stream, const Object &s);
	};

};
#endif
