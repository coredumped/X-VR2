/*
 $Id$
 
 Here we define a parent class, THE OBJECT

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
#ifdef USE_EMBEDDED_CLASSNAMES
		setClassName(xvr2::_xvr2Object);
#endif
#ifdef USE_DEBUG
#if __GNUC__ == 3 && __GNUC_MINOR__ < 4
		if(!vterm){
			std::set_terminate (__gnu_cxx::__verbose_terminate_handler);
			vterm = true;
		}
#endif
#endif
	}

#ifdef USE_EMBEDDED_CLASSNAMES
	void Object::setClassName(const char *n){
		__cls_name = (char *)n;
	}
#endif

	const char *Object::getClassName(){
#if __GNUC__ >= 3
		char *__cls_name;
		int status;
		__cls_name = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
#endif
		return (const char *)__cls_name;
	}

	void Object::debugmsg(Object *obj, const char *msg){
		if(obj == 0)
			return;
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

	void Object::debugmsgln(Object *obj, const char *msg){
		if(obj == 0)
			return;
		debugmsg(obj, msg);
		debugConsole << "\n";
	}


	Object::~Object(){
	}

	std::string Object::toString(){
		return std::string(getClassName());
	}

	std::ostream& operator<<(std::ostream& stream, const Object &s){
		stream << ((Object *)&s)->toString();
		return stream;
	}
};
