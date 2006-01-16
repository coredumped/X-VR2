/*
 * $Id$
 * 
 * This class encapsulates the thread library functionality through 
 * POSIX Threads and GNU Pth
 */
#ifdef USING_GCC3
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
#include<xvr2/Thread.h>
#include<xvr2/ThreadManager.h>
#include<xvr2/MessageStrings.h>

namespace xvr2{

	typedef struct {
		Thread *thread;
		void   *arg;
	} __thArgs_t;


	Thread::Thread(){
#if GCC_MAJOR_VERSION < 3
		setClassName(xvr2::_xvr2Thread);
#endif
		detached = true;
		policy = Thread::NORMAL;
		priority = 0;
		//pthread_attr_init(&t_attr);
	}

	unsigned long int Thread::start(){
		try{
			thread = ThreadManager::start(this);
		}
		catch(...){
			throw;
		}
		return thread;
	}

	unsigned long int Thread::start(void *arg){
		try{
			thread = ThreadManager::start(this, arg);
		}
		catch(...){
			throw;
		}
		return thread;
	}

	void Thread::detach(){
#ifdef USE_DEBUG
		debugmsgln(this, xvr2::msgDetachingThread);
#endif
#ifndef USE_GNUPTH
		pthread_detach(numericID());	
#endif
	}

	void Thread::killMe(){
#ifdef USE_GNUPTH
		pth_cancel(thread);
#else
		pthread_exit(0x00);	
#endif
	}

	bool Thread::isRunning(){
		return ThreadManager::isRunning(this);
	}

	void *Thread::run(){
		debugmsgln(this, xvr2::msgThreadOverride);
		return NULL;
	}

	void *Thread::run(void *arg){
		debugmsgln(this, xvr2::msgThreadOverride);		
		return NULL;
	}

	void Thread::setSchedulingPolicy(SchedPolicy pol){
		if(isRunning()){
			throw Exception::ThreadNotRunning();
			return;
		}
		switch(pol){
			case Thread::ROUND_ROBIN:
				//This code will set the scheduling policy to round robin
				pthread_setschedparam(thread, SCHED_RR, (sched_param *)&priority);
				policy = pol;
				break;
			case Thread::FIFO:
				//This code will set the scheduling policy to FIFO (First In First Out)
				pthread_setschedparam(thread, SCHED_FIFO, (sched_param *)&priority);
				policy = pol;
				break;
			default:
				//This code will set the scheduling policy to NORMAL
				pthread_setschedparam(thread, SCHED_OTHER, (sched_param *)&priority);
				policy = pol;
		}
	}

	void Thread::setPriority(int prio){
#ifdef USE_POSIX_THREADS
			//int pp;
			//sched_param pp;
			//pp = prio;
			switch(policy){
				case FIFO:
					pthread_setschedparam(thread, SCHED_FIFO, (sched_param *)&prio);
					break;
				case ROUND_ROBIN:
					pthread_setschedparam(thread, SCHED_RR, (sched_param *)&prio);
					break;
				default:
					pthread_setschedparam(thread, SCHED_OTHER, (sched_param *)&prio);
			}
			//pthread_attr_setschedparam((pthread_attr_t *)&t_attr, (sched_param *)&pp);
#endif
}
	unsigned long int Thread::numericID(){
		return thread;
	}

	unsigned long int Thread::numericID() const {
		return thread;
	}
	
	void *Thread::join(){
		void *ret = 0;
		if(joinable()){
#ifdef USE_POSIX_THREADS
			pthread_join(thread, &ret);
#endif
		}
		return ret;
	}

	bool Thread::joinable(){
		return (detached == true)?false:true;
	}
};
