/*
 * $Id$
 */
#include"config.h"
#include"Semaphore.h"
#include"Thread.h"
#include"ThreadManager.h"
#include"DebugConsole.h"
#ifdef USE_POSIX_THREADS
#include<pthread.h>
#endif
#include<errno.h>
#include<iostream>
#include<limits.h>

namespace xvr2{

	void Semaphore::init(int x){
		int ret;
#ifdef USE_POSIX_THREADS
		ret = sem_init(&__sem, 0, x);
#endif
		if(ret == -1){
			switch(errno){
				case EINVAL:
					throw SemaphoreInitValueException();
					break;
				default:
					throw SemaphoreException();
			}
		}
	}

	void Semaphore::destroy(){
		int ret;
#ifdef USE_POSIX_THREADS
		ret = sem_destroy(&__sem);
#endif
		if(ret == -1 && errno == EBUSY){
			throw SemaphoreUnableToDestroy();
		}
	}

	Semaphore::Semaphore(int x){
		getClassName();
		try{
			init(x);
		}
		catch(...){
			throw;
		}
	}

	Semaphore::~Semaphore(){
		try{
			destroy();
		}
		catch(...){
			throw;
		}
	}

	void Semaphore::wait(){
#ifdef USE_POSIX_THREADS
		sem_wait(&__sem);
#endif
	}

	void Semaphore::trywait(){
		int ret;
#ifdef USE_POSIX_THREADS
		ret = sem_trywait(&__sem);
#endif
		if(ret == -1 && errno == EAGAIN){
			throw SemaphoreUnableToDecrease();
		}
	}

	void Semaphore::post(){
		int ret;
#ifdef USE_POSIX_THREADS
		ret = sem_post(&__sem);
#endif
		if(ret == -1 && errno == EINVAL){
			throw SemaphoreUnableToIncrease();
		}
	}

	void Semaphore::getvalue(int *x){
#ifdef USE_POSIX_THREADS
		sem_getvalue(&__sem, x);
#endif
	}

};
