/*
 * $Id$
 */
#include"xvr2/Object.h"
#include"xvr2/TraceDumper.h"
#include"xvr2/DebugConsole.h"
#include"xvr2/TextOutput.h"
#include"xvr2/Timestamp.h"
#include"xvr2/ThreadManager.h"
#include"xvr2/Tokenizer.h"
#include"xvr2/Mutex.h"
#include <execinfo.h>
#include <signal.h>
#include <exception>
#include <iostream>
#include<cxxabi.h>

#ifndef EXCEPTION_DEPTH_TRACE
#define EXCEPTION_DEPTH_TRACE 50
#endif

namespace xvr2{
	namespace Exception{

		static xvr2::Mutex _tm;
		static bool __enabled;

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
					dm = abi::__cxa_demangle(tok2.next().toCharPtr(), 0, 0, &status);
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
			_tm.lock();
			ret = __enabled;
			_tm.unlock();
			return ret;
		}

		void ExceptionTracer::enable(){
			_tm.lock();
			__enabled = true;
			_tm.unlock();
		}

		void ExceptionTracer::disable(){
			_tm.lock();
			__enabled = false;
			_tm.unlock();
		}

		void ExceptionTracer::dumpTrace(){
			Timestamp t;
			char *demangled;
			void * array[EXCEPTION_DEPTH_TRACE];
			int nSize;
			char ** symbols;
			long int tid;
			_tm.lock();
			bzero((char *)array, EXCEPTION_DEPTH_TRACE);
		        nSize = backtrace(array, EXCEPTION_DEPTH_TRACE);
		        symbols = backtrace_symbols(array, nSize);
			debugConsole << "\n [EE] [THREAD: ";
			tid = ThreadManager::getCurrentThreadID();
			if(tid != 0){
				debugConsole << (long int)tid << "] ";
			}
			else{
				debugConsole << "MAIN] ";
			}
			debugConsole << t.toString() << "\n";
			for (int i = 0; i < nSize; i++){
				if(strstr(symbols[i], "ExceptionTracer")){
					continue;
				}
				demangled = demangle_symbol(symbols[i]);
				debugConsole << " [EE] \t" << demangled << "\n";
				free(demangled);
			}
			free(symbols);
			_tm.unlock();
		}


		ExceptionTracer::ExceptionTracer(){
#ifdef USE_DEBUG
			dumpTrace();
#else
			if(ExceptionTracer::isEnabled())
				dumpTrace();
#endif
		}

		/*void ExceptionTracer::setOutput(TextOutput *te){
			__debugConsole.setErrorOutput(te);
		}*/
	};
};
