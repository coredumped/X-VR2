/*
 $Id$
 
 Here we define a parent class, THE OBJECT

 */
#ifndef __XVR2_OBJECT_H__
#define __XVR2_OBJECT_H__
#include<xvr2config.h>
#include<_xvr2ClassNames.h>
#ifndef USE_SDL
#include<DataTypes.h>
#else
#include<SDL.h>
#endif
#include<__Destruct.h>

namespace xvr2{
	/**
	 * This one is the most primitive of all the classes, the first ancestor
	 */
	class Object{
		private:
			/**
			 * Stores the name of the current class
			 */
			char *__cls_name;
		protected:
			/**
			 * Call this method when you need to set the name of the class you're
			 * creating, typically in it's constructor, remember that you must set
			 * the classname for every class you create, that way you can have more
			 * information while debugging
			 */
#ifndef USING_GCC3
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
#ifndef USING_GCC3
			/**
			 * This constructor sets the name of the current class to <b>n</b>
			 */
			Object(const char *n){
				setClassName(n);
			}
#endif
			virtual ~Object();
			/**
			 * Will print a debug message to the screen */
			static void debugmsg(Object *obj, const char *msg);
	};
};
#endif
