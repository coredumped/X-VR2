/*
 $Id$
 
 Here we define a parent class, THE OBJECT

 */
#include<Object.h>
#include<iostream>
#include<pthread.h>
#ifdef USE_DEBUG
#include<Console.h>
#endif
#ifdef USING_GCC3
#include<stdlib.h>
#include<cxxabi.h>
#endif

namespace xvr2{
#ifdef USE_DEBUG
	extern Console __debug_console;
#ifdef USING_GCC3
#ifndef GCC_3_4
	bool vterm;
#endif
#endif
#endif
	

	Object::Object(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Object);
#endif
		__cls_name = 0;
#ifdef USE_DEBUG
#ifdef USING_GCC3
#ifndef GCC_3_4
		if(!vterm){
			std::set_terminate (__gnu_cxx::__verbose_terminate_handler);
			vterm = true;
		}
#endif
#endif
#endif
	}

#ifndef USING_GCC3
	void Object::setClassName(const char *n){
		__cls_name = (char *)n;
	}
#endif

	const char *Object::getClassName(){
#ifdef USING_GCC3
		int status;
		__cls_name = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
#endif
		return (const char *)__cls_name;
	}

	void Object::debugmsg(Object *obj, const char *msg){
		if(obj == 0)
			return;
#ifdef USE_DEBUG
		String s;
		s = obj->getClassName();
		s += "[ptr=";
		s.concat((unsigned int)obj);
		s += ",tid=";
		s.concat((unsigned int)pthread_self());
		s += "]: ";
		__debug_console.errWrite(s);
		__debug_console.errWrite(msg);
#else
		std::cout << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid=" << pthread_self() << "]: " << msg;
		std::cout.flush();
#endif
	}

#ifdef USING_GCC3
	Object::~Object(){
		if(__cls_name != 0){
			free(__cls_name);
			__cls_name = 0;
		}
	}
#endif
};
