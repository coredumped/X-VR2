/*
 *  $Id$
 *
 * This class handles thread synchronization using MUTEXes
 *
 */
#ifndef USE_GNUPTH
#ifdef GCC_2_96
#define __USE_UNIX98
#include<pthread.h>
#endif
#endif
#include<xvr2/Mutex.h>
#include<iostream>
#include<errno.h>

#ifdef DEBUG_MUTEXES
using std::cout;
using std::cerr;
using std::endl;
#endif

namespace xvr2{

Mutex::Mutex(int autoinit){
#if __GNUC__ < 3
 Object::setClassName(xvr2::_xvr2Mutex);
#endif
 if(autoinit)
  init();
}

void Mutex::init(){
#ifdef USE_GNUPTH
		pth_mutex_init(&mutex);
#else
	#ifdef USE_SDL
		mutex = SDL_CreateMutex();
	#else
		#ifdef SOLARIS
			pthread_mutex_init(&mutex, NULL);
		#else
			#ifdef USING_LINUX
				//Set error checking attributes
				#ifdef GCC_2_96
				pthread_mutex_init(&mutex, NULL);
				#else
				pthread_mutexattr_init(&m_attr);
				pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_ERRORCHECK_NP);
				pthread_mutex_init(&mutex, &m_attr);
				#endif
			#else
				pthread_mutex_init(&mutex, NULL);
			#endif
		#endif
	#endif
#endif
}

void Mutex::lock(){
#ifdef USE_GNUPTH
	/*#ifdef DEBUG_MUTEXES
		cout << "Mutex::lock " << (unsigned int)&mutex << " in " << (unsigned int)pth_self() << endl;
	#endif*/
	pth_mutex_acquire(&mutex);
#else

	#ifdef USE_SDL
	//////////////// SDL CODE STARTS HERE //////////////
		/*#ifdef DEBUG_MUTEXES
			cout << "Mutex::lock " << (unsigned int)&mutex << " in " << (unsigned int)SDL_ThreadID() << endl;
		#endif*/
		if(SDL_mutexP(mutex) == -1)
			throw Exception::UnableToLockMutex();
	//////////////// SDL CODE ENDS HERE //////////////
	#else
 
 
		int err_code;
		if((err_code = pthread_mutex_lock(&mutex)) != 0){
#ifdef USING_LINUX
				if(err_code == EDEADLK){
#ifdef DEBUG_MUTEXES
					//cerr << "Mutex: " << (unsigned int)&mutex << " in " << (unsigned int)SDL_ThreadID() <<  " will create a DEADLOCK " << endl;
					debugmsgln(this, "DEADLOCK detected");
#endif
					throw Exception::DeadLock();
				}
				else if(err_code == EINVAL){
					debugmsgln(this, " MUTEX HAS NOT BEEN INITIALIZED CORRECTLY!!!!");
					throw Exception::UnableToLockMutex();
				}
#else
				throw Exception::UnableToLockMutex();
#endif
		}
	#endif



#endif
#ifdef DEBUG_MUTEXES
	//cout << "Mutex::lock " << (unsigned int)&mutex << " in " << (unsigned int)pthread_self() << endl;
	debugmsgln(this, "Locked");
#endif
}


void Mutex::unlock(){
#ifdef USE_GNUPTH
	pth_mutex_release(&mutex);
/*#ifdef DEBUG_MUTEXES
 cout << "Mutex::unlock " << (unsigned int)&mutex << " in " << (unsigned int)pth_self() << endl;
#endif*/
#else
	#ifdef USE_SDL
	//////////////// SDL CODE STARTS HERE //////////////
		if(SDL_mutexV(mutex) == -1)
			throw Exception::UnableToUnlockMutex();
		/*#ifdef DEBUG_MUTEXES
			cout << "Mutex::unlock " << (unsigned int)&mutex << " in " << (unsigned int)SDL_ThreadID() << endl;
		#endif*/
	//////////////// SDL CODE ENDS HERE //////////////
	 #else
		 if(pthread_mutex_unlock(&mutex) != 0)
			 throw Exception::UnableToUnlockMutex();
		/*#ifdef DEBUG_MUTEXES
			cout << "Mutex::unlock " << (unsigned int)&mutex << " in " << (unsigned int)pthread_self() << endl;
		#endif*/
	#endif
#endif
#ifdef DEBUG_MUTEXES
	debugmsgln(this, "Unlocked");
#endif
}

void Mutex::destroy(){
#ifdef USE_SDL
 SDL_DestroyMutex(mutex);
#else
#ifndef USE_GNUPTH
 pthread_mutex_destroy(&mutex);
#ifdef USING_LINUX
 pthread_mutexattr_destroy(&m_attr);
#endif
#endif
#endif
}

};
