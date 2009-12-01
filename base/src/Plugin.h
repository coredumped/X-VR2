/*
 * $Id$
 */
#ifndef __XVR2_PLUGIN_H__
#define __XVR2_PLUGIN_H__
#include<System.h>
#include<Exception.h>
#include<String.h>
#include<DSOException.h>

#ifndef _WIN32

namespace xvr2{
	/**
	 * This is the plugin class, it adds an interface for loading dynamic 
	 * shared objects to your program
	 */
	class Plugin:public System{
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
			Plugin();
			/** This constructor initializes on the <b>handle</b> 
			 * and <b>loaded</b> variables, also it initializes the
			 * name of the dso
			 */
			Plugin(const String &plName);
			~Plugin();
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
			void load(String plName);
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
			String &getDSOName();
	};

}
#else
#warning "There's no portability for the windows side yet"
#endif

#endif

