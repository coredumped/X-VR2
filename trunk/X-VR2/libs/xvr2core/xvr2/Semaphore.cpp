/*
 * $Id$
 */
#include"config.h"
#include"Semaphore.h"
#include"Thread.h"
#include"ThreadManager.h"
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
#ifdef USE_DEBUG
		debugmsg(this, "Initializing");
#endif
		if(ret == -1){
			switch(errno){
				case EINVAL:
#ifdef USE_DEBUG
					debugmsg(this, "invalid value.");
#endif
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
#if __GNUC__ < 3
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

	void Semaphore::debugmsg(Semaphore *obj, const char *msg){
		int y;
		Thread *t;
		getvalue(&y);
		t = (Thread *)ThreadManager::getCurrentThread();
#if __WORDSIZE == 64 && defined(__x86_64__)
		if(t == 0){
			std::cout << obj->getClassName() << "[ptr=" << (unsigned long)obj << ",tid=[MAIN],val=" << y << "]: " << msg;
		}
		else{
			std::cout << obj->getClassName() << "[ptr=" << (unsigned long)obj << ",tid=" << t->numericID() << ",val=" << y << "]: " << msg;
		}
#else
		if(t == 0){
			std::cout << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid=[MAIN],val=" << y << "]: " << msg;
		}
		else{
			std::cout << obj->getClassName() << "[ptr=" << (unsigned int)obj << ",tid=" << t->numericID() << ",val=" << y << "]: " << msg;
		}
#endif
		std::cout.flush();
	}
};
