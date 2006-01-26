/*
 * $Id$
 */
#ifndef __XVR2_THREAD_MANAGER_H__
#define __XVR2_THREAD_MANAGER_H__
#include<xvr2/Threading.h>
#include<xvr2/Thread.h>
#include<xvr2/ThreadException.h>

namespace xvr2 {

	class ThreadManager:public Threading {
		private:
			static void addThread(Thread *t, unsigned long int id);
			static void removeThread(Thread *t, unsigned long int id);
		protected:
			static void *runMethod(void *t);
			static void *runMethod_arg(void *t);
		public:
			/** Spawns thread t execution */
			static unsigned long int start(Thread *t);
			/** Spawns thread t execution */
			static unsigned long int start(Thread *t, void *arg);
			/** Tells wheter the t is running or not */
			static bool isRunning(Thread *t);
			/** Returns the currently running Thread Object or 0 if the method is called from a non-Thread.*/
			static const Thread *getCurrentThread();
			static const unsigned long int getCurrentThreadID();
			/** Returns how many threads are actively running. */
			static unsigned int activeCount();
	};

};

#endif
