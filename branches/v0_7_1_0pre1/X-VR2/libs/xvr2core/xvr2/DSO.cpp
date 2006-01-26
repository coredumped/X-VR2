/*
 * $Id$
 */
#include"config.h"
#include"DSO.h"
#ifndef _WIN32
#include<dlfcn.h>
#include"MessageStrings.h"

namespace xvr2{

	DSO::DSO(){
		loaded = false;
		handle = 0;
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2DSO);
#endif
		dso = (char *)msgNothingLoaded;
	}

	DSO::~DSO(){
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
			std::cerr << " DSO::~DSO " << std::endl;
	#endif
#endif
		unload();
	}
	
	DSO::DSO(const String &plName){
		loaded = false;
		handle = 0;
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2DSO);
#endif
		dso = plName.toCharPtr();
	}

	void DSO::load(){
		handle = dlopen(dso.toCharPtr(), RTLD_NOW);
		if(!handle){
#ifdef USE_DEBUG
			std::cerr << "Error while loading \"" << dso.toCharPtr() << "\"\t" << dlerror() << std::endl;
#endif
			throw CantLoadDSO();
		}
	}

	void DSO::load(const String &plName){
		dso = plName;
		load();
	}

	void DSO::unload(){
		if(handle != 0){
#ifdef USE_DEBUG
			std::cerr << " DSO::unload " << std::endl;
#endif
			if(dlclose(handle) != 0){
				throw CantUnloadDSO();
			}
			handle = 0;
		}
	}

	void *DSO::getSymbol(const String &sym){
		void *ptr;
		if(!handle)
			throw DSO("Load the DSO first!!!");
#ifdef USE_DEBUG
		std::cerr << "\tloading: " << sym.toCharPtr() << "... ";
#endif
		ptr = dlsym(handle, sym.toCharPtr());
		if(ptr == 0){
			throw DSOSymbol();
		}
#ifdef USE_DEBUG
		std::cerr << "done" << std::endl;
#endif
		return ptr;
	}
}

#endif
