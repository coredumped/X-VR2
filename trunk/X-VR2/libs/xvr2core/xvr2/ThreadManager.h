/*
 * $Id$
 */
#ifndef __XVR2_THREAD_MANAGER_H__
#define __XVR2_THREAD_MANAGER_H__
#include<xvr2/Threading.h>
#include<xvr2/Thread.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/BackgroundFunction.h>

namespace xvr2 {

	/** \class ThreadManager ThreadManager.h <xvr2/ThreadManager.h>
	 *  \brief
	 *  This class brings basic thread creation management functions, and permits
	 *  running a function in the background. */
	class ThreadManager:public Threading {
		private:
			static void addThread(Thread *t, unsigned long int id);
			static void removeThread(Thread *t, unsigned long int id);
		protected:
			static void *runMethod(void *t);
			static void *runMethod_arg(void *t);
			static void *runMethod_bf(BackgroundFunction &bf);
		public:
			/** Spawns thread t execution.
			 *  \param t Thread to be started */
			static unsigned long int start(Thread *t);
			/** Spawns thread t execution. 
			 *  \param t Thread object to be started.
			 *  \param arg The arguments to be passed to the thread being started. */
			static unsigned long int start(Thread *t, void *arg);
			/** Runs a Background function in a dedicated Thread of execution.
			 *  \param bf The BackgroundFunction to be runned.
			 *  \param waitfor If true the start method wont return until the thread has been succesfully started. */
			static unsigned long int start(BackgroundFunction &bf, bool waitfor = true);
			/** Tells wheter the t is running or not 
			 *  \param t The thread to be verified. */
			static bool isRunning(Thread *t);
			/** Returns the currently running Thread Object or 0 if the method is called from a non-Thread.*/
			static const Thread *getCurrentThread();
			/** Returns the numeric id of the currently running Thread */
			static const unsigned long int getCurrentThreadID();
			/** Returns how many threads are actively running. */
			static unsigned int activeCount();
	};

};

#endif
