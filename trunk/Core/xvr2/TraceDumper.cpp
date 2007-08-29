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
#include"Object.h"
#include"TraceDumper.h"
#include"DebugConsole.h"
#include"TextOutput.h"
#include"Timestamp.h"
#include"ThreadManager.h"
#include"Tokenizer.h"
#include"Mutex.h"
#include"StringBuffer.h"
#ifdef USING_LINUX
#include<execinfo.h>
#else

#ifdef USING_SOLARIS
#include<ucontext.h>
#endif

#endif
#include<signal.h>
#include<exception>
#include<iostream>
#include<cxxabi.h>

#ifndef EXCEPTION_DEPTH_TRACE
#define EXCEPTION_DEPTH_TRACE 1024
#endif

/*TODO: Add source address translation, like addr2line on Linux systems. */

namespace xvr2{
#ifdef __GNUC__
	static const char *__gxx_p1 = "__gxx_personality";
#endif
#if defined(__linux__) || defined(__linux) || defined(_linux)
	static const char *__gxx_p2 = "cmov";
	static const char *__gxx_p3 = "/lib/tls/i";
#endif
	//static xvr2::Mutex _tm;
	static bool __enabled;
#ifdef USE_POSIX_THREADS
	static pthread_mutex_t _tm;
	static bool __inited = false;
	static pthread_mutexattr_t _tm_attr;
#endif
	
	static StringBuffer __StackTrace;

	static char *demangle_symbol(const char *symbol){
		char *ret, *dm;
		int status;
		//1. Extract C++ classname or function name
		//2. Demangle it
		//3. Reintegrate it to the rest of the symbol string
		if(strstr(symbol, "(")){
			String tmp;
			String first, last;
			Tokenizer tok(symbol, "(");
			first = tok.next();
			tmp = tok.next();
			if(tmp.index("+") == -1){
				//No parameters
				ret = strdup(symbol);
			}
			else{
				//Has parameters
				Tokenizer tok2(tmp, "+");
				dm = abi::__cxa_demangle(
										tok2.next().toCharPtr(), 
										0, 0, &status
									);
				if(status == 0){
					first.concat("(");
					first.concat(dm);
					first.concat("+");
					first.concat(tok2.next());
					ret = strdup(first.toCharPtr());
				}
				else{
					ret = strdup(symbol);
				}
				free(dm);
			}
		}
		else{
			ret = strdup(symbol);
		}
		return ret;
	}

	bool ExceptionTracer::isEnabled(){
		bool ret;
#ifdef USE_POSIX_THREADS
		pthread_mutex_lock(&_tm);
#endif
		ret = __enabled;
#ifdef USE_POSIX_THREADS
		pthread_mutex_unlock(&_tm);
#endif
		return ret;
	}

	void ExceptionTracer::enable(){
#ifdef USE_POSIX_THREADS
		pthread_mutex_lock(&_tm);
#endif
		__enabled = true;
#ifdef USE_POSIX_THREADS
		pthread_mutex_unlock(&_tm);
#endif
	}

	void ExceptionTracer::disable(){
#ifdef USE_POSIX_THREADS
		pthread_mutex_lock(&_tm);
#endif
		__enabled = false;
#ifdef USE_POSIX_THREADS
		pthread_mutex_unlock(&_tm);
#endif
	}

#ifdef USING_LINUX
	/////////////////////// LINUX CODE STARTS HERE ////////////////////////////
	void ExceptionTracer::dumpTrace(){
		Timestamp t;
		char *demangled;
		void * array[EXCEPTION_DEPTH_TRACE];
		int nSize;
		char ** symbols;
		Int64 tid;
#ifdef USE_POSIX_THREADS
		pthread_mutex_lock(&_tm);
#endif
		__StackTrace.clear();
		bzero((char *)array, EXCEPTION_DEPTH_TRACE);
	        nSize = ::backtrace(array, EXCEPTION_DEPTH_TRACE);
	        symbols = backtrace_symbols(array, nSize);
		debugConsole << "\n [EE] [THREAD: ";
		tid = ThreadManager::getCurrentThreadID();
		if(ThreadManager::currentIsMain()){
			debugConsole << "MAIN] ";
		}
		else{
			debugConsole << (Int64)tid << "] ";
		}
		debugConsole << t.toString() << "\n";
		for (int i = 0; i < nSize; i++){
			if(strstr(symbols[i], "ExceptionTracer")){
				continue;
			}
			demangled = demangle_symbol(symbols[i]);
#if defined(__linux__) || defined(__linux) || defined(_linux)
			if(strstr(demangled, __gxx_p1) == 0 && 
						strstr(demangled, __gxx_p2) == 0 && 
						strstr(demangled, __gxx_p3) == 0){
				debugConsole << " " << demangled << "\n";
				__StackTrace << " " << demangled << "\n";
			}
#else
#ifdef __GNUC__
			if(strstr(demangled, __gxx_p1) == 0){
				debugConsole << " " << demangled << "\n";
				__StackTrace << " " << demangled << "\n";
			}
#else
			__StackTrace << " " << demangled << "\n";
#endif
#endif
			free(demangled);
		}
		free(symbols);
#ifdef USE_POSIX_THREADS
		pthread_mutex_unlock(&_tm);
#endif
	}
	//////////////////////// LINUX CODE ENDS HERE /////////////////////////////
#else
#ifdef USING_SOLARIS
	////////////////////// SOLARIS CODE STARTS HERE ////////////////////////////
	void ExceptionTracer::dumpTrace(){
		//@todo: Implement OpenSolaris walkcontext
		printstack(2);
	}
	/////////////////////// SOLARIS CODE ENDS HERE /////////////////////////////
#endif

#endif

	ExceptionTracer::ExceptionTracer(){
#ifdef USE_POSIX_THREADS
		if(!__inited){
			pthread_mutexattr_init(&_tm_attr);
			pthread_mutexattr_settype(&_tm_attr, PTHREAD_MUTEX_ERRORCHECK_NP);
			pthread_mutex_init(&_tm, &_tm_attr);
		}
#endif
#ifdef USE_DEBUG
		dumpTrace();
#else
		if(ExceptionTracer::isEnabled())
			dumpTrace();
#endif
	}

	const char *ExceptionTracer::backtrace(){
		return __StackTrace.toString().c_str();
	}
};
