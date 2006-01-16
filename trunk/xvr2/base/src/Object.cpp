/*
 $Id$
 
 Here we define a parent class, THE OBJECT

 */
#include<xvr2/Object.h>
#include<iostream>
#include<xvr2/DebugConsole.h>
#if GCC_MAJOR_VERSION >= 3
#include<stdlib.h>
#include<cxxabi.h>
#endif
#include"xvr2/ThreadManager.h"
#include<limits.h>

namespace xvr2{
//#ifndef GCC_3_4
#if GCC_MAJOR_VERSION == 3 && GCC_MINOR_VERSION < 4
	bool vterm;
#endif
	

	Object::Object(){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Object);
#endif
#ifdef USE_DEBUG
#if GCC_MAJOR_VERSION == 3 && GCC_MINOR_VERSION < 4
		if(!vterm){
			std::set_terminate (__gnu_cxx::__verbose_terminate_handler);
			vterm = true;
		}
//#endif
#endif
#endif
		string_representation = 0;
	}

#if GCC_MAJOR_VERSION < 3
	void Object::setClassName(const char *n){
		__cls_name = (char *)n;
	}
#endif

	const char *Object::getClassName(){
#if GCC_MAJOR_VERSION >= 3
		char *__cls_name;
		int status;
		__cls_name = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
#endif
		return (const char *)__cls_name;
	}

	void Object::debugmsg(Object *obj, const char *msg){
		if(obj == 0)
			return;
#if __WORDSIZE == 64 && defined(__86_64__)
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
		delete string_representation;
		string_representation = 0;
	}

	const std::string &Object::toString(){
		if(string_representation == 0){
			string_representation = new std::string(getClassName());
		}
		return *string_representation;
	}

	std::ostream& operator<<(std::ostream& stream, const Object &s){
		stream << ((Object *)&s)->toString();
		return stream;
	}
};
