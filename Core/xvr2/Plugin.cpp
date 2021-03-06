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
#include"config.h"
#include "Plugin.h"
#ifndef _WIN32
#include<dlfcn.h>
#include "MessageStrings.h"
#include "DebugConsole.h"

namespace xvr2{

	Plugin::Plugin(){
		loaded = false;
		handle = 0;
		dso = (char *)msgNothingLoaded;
	}

	Plugin::~Plugin(){
#ifdef USE_DEBUG
	#if DEBUG_LEVEL == 5
			debugConsole << " Plugin::~Plugin\n";
	#endif
#endif
		unload();
	}
	
	Plugin::Plugin(const String &plName){
		loaded = false;
		handle = 0;
		dso = plName.toCharPtr();
	}

	void Plugin::load(){
		handle = dlopen(dso.toCharPtr(), RTLD_NOW);
		if(!handle){
#ifdef USE_DEBUG
			debugConsole << "Error while loading \"" << dso << "\"\t" << dlerror() << "\n";
#endif
			throw CantLoadDSO();
		}
	}

	void Plugin::load(const String &plName){
		dso = plName;
		load();
	}

	void Plugin::unload(){
		if(handle != 0){
#ifdef USE_DEBUG
			debugConsole << " Plugin::unload\n";
#endif
			if(dlclose(handle) != 0){
				throw CantUnloadDSO();
			}
			handle = 0;
		}
	}

	void *Plugin::getSymbol(const String &sym){
		void *ptr;
		if(!handle)
			throw DSOException("Load the DSO first!!!");
#ifdef USE_DEBUG
		debugConsole << "\tloading: " << sym.toCharPtr() << "... ";
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
