/*
 * $Id$
 */
#ifndef __XVR2_DSO_H__
#define __XVR2_DSO_H__
#include<xvr2/System.h>
#include<xvr2/String.h>
#include<xvr2/CoreExceptions.h>

#ifndef _WIN32

namespace xvr2{
	/**
	 * This is the plugin class, it adds an interface for loading dynamic 
	 * shared objects to your program
	 */
	class DSO:public System{
		protected:
			/**
			 * Holds the filename of the shared object itself
			 */
			String dso;
			/**
			 * Tells if the object is loaded or not
			 */
			bool loaded;
			/**
			 * This is the handle value as returned by the dlopen
			 * function
			 */
			void *handle;
		public:
			/** Default constructor this one does nothing but a few
			 * initializations on the <b>handle</b> and <b>loaded</b>
			 * variables
			 */
			DSO();
			/** This constructor initializes on the <b>handle</b> 
			 * and <b>loaded</b> variables, also it initializes the
			 * name of the dso
			 */
			DSO(const String &plName);
			~DSO();
			/**
			 * Loads the dso into memory, this method requires the
			 * use of the second constructor, not the default one if
			 * you've used the default then you shold probably use
			 * the another <b>load</b> method
			 */
			void load();
			/**
			 * Loads the dso defined by <b>plName</b> and updates the
			 * contents of the dso variable name
			 */
			void load(const String &plName);
			/**
			 * Unloads the dso from memory
			 */
			void unload();
			/**
			 * Use this method whenever you want to obtain a symbol
			 * from the dso
			 */
			void *getSymbol(const String &sym);
			/**
			 * This method returns the name of the dso itself
			 */
			const String &getDSOName();
			template<class T>
			inline T *createObject(const String &createfuncname = "__xvr2_create_dsobject"){
				T *obj = 0;
				T *(*dso_create)();
				dso_create = (T * (*)())getSymbol(createfuncname);
				obj = dso_create();
				return obj;
			}
			template<class T>
			inline void destroyObject(T *obj, const String &destroyfuncname = "__xvr2_destroy_dsobject"){
				void (*dso_destroy)(T *);
				dso_destroy = (void (*)(T *))getSymbol(destroyfuncname);
				dso_destroy(obj);
			}
		
			/**
			 * Tells whenever the dso file has been loaded or not
			 */
			bool isLoaded(){
				return loaded;
			}
	};

}
#else
#warning "There's no portability for the windows side yet"
#endif

#endif
