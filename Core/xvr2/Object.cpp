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
#include "Object.h"
#include<iostream>
#include "DebugConsole.h"
#if __GNUC__ >= 3
#include<stdlib.h>
#include<cxxabi.h>
#endif
#include"ThreadManager.h"
#include<limits.h>

namespace xvr2{
#if __GNUC__ == 3 && __GNUC_MINOR__ < 4
	bool vterm;
#endif
	

	Object::Object(){
#ifdef USE_DEBUG
#if __GNUC__ == 3 && __GNUC_MINOR__ < 4
		if(!vterm){
			std::set_terminate (__gnu_cxx::__verbose_terminate_handler);
			vterm = true;
		}
#endif
#endif
		this->getClassName();
	}

	const char *Object::getClassName(){
		/*char *__cls_name;
		int status;
		__cls_name = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
		return (const char *)__cls_name;*/
		char *tmp;
		int status;
		tmp = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
		if(status == 0){
			__cls_name = tmp;
			free(tmp);
		}
		return __cls_name.c_str();
	}

	void Object::debugmsg(Object *obj, const char *msg, int linenumber, const char *srcfile){
		if(obj == 0)
			return;
		if(linenumber >= 0)
			debugConsole << srcfile << ":" << linenumber << ": ";
#if __WORDSIZE == 64 && defined(__x86_64__)
		debugConsole << obj->getClassName() << "[ptr=" << (Int64)obj << ",tid=";
#else
		debugConsole << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid=";
#endif
		if(ThreadManager::getCurrentThreadID() == 0){
			debugConsole << "MAIN";
		}
		else{
			debugConsole << (unsigned int)ThreadManager::getCurrentThreadID();
		}
		debugConsole << "]: " << msg;
	}

	void Object::debugmsgln(Object *obj, const char *msg, int linenumber, const char *srcfile){
		if(obj == 0)
			return;
		debugmsg(obj, msg, linenumber, srcfile);
		debugConsole << "\n";
	}


	Object::~Object(){
	}

	/*std::string Object::toString(){
		return std::string(getClassName());
	}*/
	
	std::string Object::toString() {
		getClassName();
		//return std::string(getClassName());
		//return std::string(abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status));
		return __cls_name;
	}

	std::ostream& operator<<(std::ostream& stream, const Object &s){
		stream << ((Object *)&s)->toString();
		return stream;
	}
}
