/*
 * $Id$
 */
#include<Plugin.h>
#ifndef _WIN32
#include<dlfcn.h>
#include<MessageStrings.h>

namespace xvr2{

	Plugin::Plugin(){
		loaded = false;
		handle = 0;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Plugin);
#endif
		dso = (char *)msgNothingLoaded;
	}

	Plugin::~Plugin(){
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
			std::cerr << " Plugin::~Plugin " << std::endl;
	#endif
#endif
		unload();
	}
	
	Plugin::Plugin(const String &plName){
		loaded = false;
		handle = 0;
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Plugin);
#endif
		dso = ((String *)&plName)->toCharPtr();
	}

	void Plugin::load(){
		handle = dlopen(dso.toCharPtr(), RTLD_NOW);
		if(!handle){
#ifdef USE_DEBUG
			std::cerr << "Error while loading \"" << dso.toCharPtr() << "\"\t" << dlerror() << std::endl;
#endif
			throw Exception::CantLoadDSO();
		}
	}

	void Plugin::load(String plName){
		dso = plName;
		load();
	}

	void Plugin::unload(){
		if(handle){
#ifdef USE_DEBUG
			std::cerr << " Plugin::unload " << std::endl;
#endif
			if(dlclose(handle) != 0){
				throw Exception::CantUnloadDSO();
			}
			handle = 0;
		}
	}

	void *Plugin::getSymbol(const String &sym){
		void *ptr;
		String *s;
		if(!handle)
			throw Exception::DSO("Load the DSO first!!!");
		s = (String *)&sym;
#ifdef USE_DEBUG
		std::cerr << "\tloading: " << s->toCharPtr() << "... ";
#endif
		ptr = dlsym(handle, s->toCharPtr());
		if(ptr == 0){
			throw Exception::DSOSymbol();
		}
#ifdef USE_DEBUG
		std::cerr << "done" << std::endl;
#endif
		return ptr;
	}
}

#endif
