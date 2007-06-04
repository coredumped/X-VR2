/*
 * $Id$
 * 
 * This class encapsulates the thread library functionality through 
 * POSIX Threads and GNU Pth
 */
#include"config.h"
#if __GNUC__ >= 3
#include<iostream>
#else
#include<iostream.h>
#endif
#include<errno.h>
#ifdef USE_GNUPTH
#include<pth.h>
#endif
#include<stdlib.h>
#include<errno.h>
#include "Thread.h"
#include "ThreadManager.h"
#include "MessageStrings.h"

namespace xvr2{

	Thread::Thread(){
		_started = false;
		_terminated = false;
		_detached = false;
	}
	Thread::~Thread(){ }

	void Thread::start(){
		try{
			ThreadManager::start(this);
		}
		catch(...){
			throw;
		}
	}

	void Thread::start(Threading::SchedPolicy pol){
		try{
			ThreadManager::start(this, pol);
		}
		catch(...){
			throw;
		}
	}

	void Thread::killMe(){
#ifdef USE_POSIX_THREADS
		pthread_exit(0x00);	
#else
		pth_cancel(thread);
#endif
	}

	bool Thread::isRunning(){
		return (_terminated==false)?true:false;
	}

	void Thread::setPriority(int prio){
		ThreadManager::setPriority(this, prio);
	}
	UInt64 Thread::numericID(){
		return ThreadManager::numericID(this);
	}

	UInt64 Thread::numericID() const {
		return ThreadManager::numericID(this);
	}
	
	const bool Thread::joinable(){
		return (_detached == true)?false:true;
	}
};
