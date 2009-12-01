/*
 * $Id$
 */
#ifndef __XVR2_DS_OBJECT_H__
#define __XVR2_DS_OBJECT_H__
#include<xvr2/Object.h>
#include<xvr2/String.h>
#include<xvr2/DSO.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {

	/* DSObject stands for Dynamic Shared Object and is a for to load a C++ object
	 * from a shared library, in the same way you load a funciotns using the Plugin
	 * class */
	class DSObjectFactory : public Object {
		private:
		protected:
		public:
			template<class T>
			static T *create(DSO *dso, const String &createfuncname = "__xvr2_create_dsobject"){
				T *obj = 0;
				T *(*dso_create)();
				dso_create = (T * (*)())dso->getSymbol(createfuncname);
				obj = dso_create();
				return obj;
			}
			template<class T>
			static void destroy(DSO *dso, T *obj, const String &destroyfuncname = "__xvr2_destroy_dsobject"){
				void (*dso_destroy)(T *);
				dso_destroy = (void (*)(T *))dso->getSymbol(destroyfuncname);
				dso_destroy(obj);
			}
	};

};

#endif
