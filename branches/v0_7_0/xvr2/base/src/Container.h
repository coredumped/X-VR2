/*
 * $Id$
 */
#ifndef __XVR2_CONTAINER_H__
#define __XVR2_CONTAINER_H__
#include<xvr2/Object.h>
#include<xvr2/Exception.h>

namespace xvr2{
	namespace Util {
		/**
		 * This class is an interface for the container classes
		 */
		class Container:public Object{
			protected:
				/**
				 * Keeps a count of the number of elements contained in the
				 * list
				 */
				unsigned int num_data;
			public:
				/**
				 * Default Constructor for the container classes
				 */
				Container();
				/**
				 * This one just calls setClassName from Object
				 */
				Container(const char *);
				/**
				 * Returns the size of the given list
				 */
				unsigned int size(){
					return num_data;
				}
		};
	};
};

#endif
