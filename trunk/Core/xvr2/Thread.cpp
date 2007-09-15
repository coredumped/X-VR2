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
#if __GNUC__ >= 3
#include<iostream>
#else
#include<iostream.h>
#endif
#include<errno.h>
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
}
