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
#ifndef __XVR2_THREAD_H__
#define __XVR2_THREAD_H__

#include<xvr2/Object.h>
#ifdef USE_POSIX_THREADS
#include<pthread.h>
#else
#include<pth.h>
#endif

#include<xvr2/Mutex.h>
#include<xvr2/SharedVar.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/ThreadFinalizator.h>
#include<xvr2/Threading.h>

namespace xvr2{

	class Thread:public ThreadFinalizator{
		private:
		protected:
			/** Default constructor */
			Thread();
			bool _detached;

		public:
			SharedVar<int> schedPolicy;
			/** Status flag which determinates if the run method
			 *  has been called from the thread after calling start */
			SharedVar<bool> _started;
			/** Status flag which determinates if the run method
			 *  has finished its execution. */
			SharedVar<bool> _terminated;
			/** This is the class destructor, it simply
			 *  calls detach for cleanup purposes */
			virtual ~Thread();
			/** Call this method when you want to start running
			 *  your thread, however please note that everytime
			 *  you call this method, the thread will be
			 *  spawned again as a totally new instance. */
			virtual void start();
			virtual void start(Threading::SchedPolicy pol);
			/** <b>Very important</b>\n
			 * You must override this method so you can provide
			 * the thread process itself
			 * whatever you define this method does, in your
			 * subclass is what the thread
			 * will start doing when you call start(). */
			virtual void operator()() = 0;
			/**
			 * Use this method to verify if your thread
			 * is running; */
			bool isRunning();

			/** Use this method to set the priority for the
			 *  current scheduling policy.  */
			void setPriority(int prio);
			/** This method will return a 64 bit integer
			 *  representing the current thread id.*/
			UInt64 numericID();
			/** This method will return a 64 bit integer
			 *  representing the current thread id.*/
			UInt64 numericID() const ;
			bool started();
			bool terminated();
			bool running();
			bool joinable();

			void join();
	};

}

#endif
