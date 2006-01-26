/*
 * $Id$
 */
#ifndef __XVR2_MUTEX_H__
#define __XVR2_MUTEX_H__

#ifdef USE_GNUPTH
#include<pth.h>
#else
#ifdef USE_SDL
#include<xvr2/SDL.h>
#else
#include<pthread.h>
#endif
#endif

#include<xvr2/MutexException.h>
#include<xvr2/Threading.h>
namespace xvr2{

	/**
	 * This classes handle MUTEX (MUTual EXclusion) sinchronization devices<br>
	 * This classes are designed to work with SDL's Thread encapsulation, 
	 * GNU Pth or POSIX Threads
	 */
	class Mutex:public Threading{
	 private:
	  /**
	   * Destroys the current mutex, freeing all the resources allocated
	   * by it
	   */
	  void destroy();
	 public:
	  /** The mutex object itself as defined by POSIX Threads GNU Pth or SDL */
#ifdef USE_GNUPTH
	  pth_mutex_t mutex;
#else
#ifdef USE_SDL
	    SDL_mutex *mutex;
#else
            pthread_mutex_t mutex;
	    pthread_mutexattr_t m_attr;
#endif
	#endif
	  /**
	   * Constructor initialize using default atttributes, this depends on how
	   * you compiled the library if you chose GNU Pth then the first argument
	   * is meaningfull
	   */
	  Mutex(int autoinit = 1);
	  /**
	   * This destructor calls dastroy to ensure that all the resources used
	   * by the Mutex all released automagically
	   */
	  virtual ~Mutex(){
		  destroy();
	  }
	
	  /** 
	   * Initializer, use in case of not using the default constructor
	   * (this interface is provided for future compatibility)
	   * */
	  void init();
	
	  /**
	   * Use this to explicitely lock the mutex
	   */
	  void lock();
	
	  /**
	   * Use this to explicitely unlock the mutex
	   */
	  void unlock();
	};

};

#endif
