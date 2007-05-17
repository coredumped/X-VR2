/*
 * $Id$
 */
#include<Exception.h>
#include<Semaphore.h>
#include<Thread.h>
#ifdef USE_POSIX_THREADS
#include<pthread.h>
#endif
#include<errno.h>
#include<iostream>

namespace xvr2{

	void Semaphore::init(int x){
		int ret;
#ifdef USE_POSIX_THREADS
		ret = sem_init(&__sem, 0, x);
#endif
#ifdef USE_DEBUG
		debugmsg(this, "Initializing");
#endif
		if(ret == -1){
			switch(errno){
				case EINVAL:
#ifdef USE_DEBUG
					debugmsg(this, "invalid value.");
#endif
					throw Exception::SemaphoreInitValue();
					break;
				default:
					throw Exception::Semaphore();
			}
		}
	}

	void Semaphore::destroy(){
		int ret;
#ifdef USE_POSIX_THREADS
		ret = sem_destroy(&__sem);
#endif
		if(ret == -1 && errno == EBUSY){
			throw Exception::SemaphoreUnableToDestroy();
		}
	}

	Semaphore::Semaphore(int x){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Semaphore);
#endif
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
			throw Exception::SemaphoreUnableToDecrease();
		}
	}

	void Semaphore::post(){
		int ret;
#ifdef USE_POSIX_THREADS
		ret = sem_post(&__sem);
#endif
		if(ret == -1 && errno == EINVAL){
			throw Exception::SemaphoreUnableToIncrease();
		}
	}

	void Semaphore::getvalue(int *x){
#ifdef USE_POSIX_THREADS
		sem_getvalue(&__sem, x);
#endif
	}

	void Semaphore::debugmsg(Semaphore *obj, const char *msg){
		int y;
		getvalue(&y);
		std::cout << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid=" << Thread::numericID() << ",val=" << y << "]: " << msg;
		std::cout.flush();
	}
};
