/*
 * $Id$
 */
#include"config.h"
#include"DSO.h"
#ifndef _WIN32
#include<dlfcn.h>
#include"MessageStrings.h"
#include"DebugConsole.h"

namespace xvr2{

	DSO::DSO(){
		loaded = false;
		handle = 0;
#ifdef USE_EMBEDDED_CLASNAMES
		setClassName(xvr2::_xvr2DSO);
#endif
		dso = (char *)msgNothingLoaded;
	}

	DSO::~DSO(){
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
			debugConsole << " DSO::~DSO\n";
	#endif
#endif
		unload();
	}
	
	DSO::DSO(const String &plName){
		loaded = false;
		handle = 0;
#if USE_EMBEDDED_CLASNAMES
		setClassName(xvr2::_xvr2DSO);
#endif
		dso = plName.toCharPtr();
	}

	void DSO::load(){
		handle = dlopen(dso.toCharPtr(), RTLD_NOW);
		if(!handle){
#ifdef USE_DEBUG
			debugConsole << "Error while loading \"" << dso << "\"\t" << dlerror() << "\n";
#endif
			throw CantLoadDSO();
		}
		loaded = true;
	}

	void DSO::load(const String &plName){
		dso = plName;
		load();
	}

	void DSO::unload(){
		if(handle != 0){
#ifdef USE_DEBUG
			debugConsole << " DSO::unload " << "\n";
#endif
			if(dlclose(handle) != 0){
				throw CantUnloadDSO();
			}
			handle = 0;
			loaded = false;
		}
	}

	void *DSO::getSymbol(const String &sym){
		void *ptr;
		if(!handle)
			throw DSO("Load the DSO first!!!");
#ifdef USE_DEBUG
		debugConsole << "\tloading: " << sym << "... ";
#endif
		ptr = dlsym(handle, sym.toCharPtr());
		if(ptr == 0){
			throw DSOSymbolException();
		}
#ifdef USE_DEBUG
		debugConsole << "done\n";
#endif
		return ptr;
	}
}

#endif
