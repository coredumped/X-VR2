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
#ifndef __XVR2_THREAD_MANAGER_H__
#define __XVR2_THREAD_MANAGER_H__
#include<xvr2/Threading.h>
#include<xvr2/Thread.h>
#include<xvr2/JoinableThread.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/InvalidParameterException.h>
#include<xvr2/BackgroundFunction.h>

namespace xvr2 {

	/** \class ThreadManager ThreadManager.h <xvr2/ThreadManager.h>
	 *  \brief
	 *  This class brings basic thread creation management functions, and permits
	 *  running a function in the background. */
	class ThreadManager:public Threading {
		private:
		protected:
		public:
			/** Spawns thread t execution.
			 *  @param t Thread to be started */
			static void start(Thread *t);
			static void start(Thread &t);
			/** @brief Spawns a thread object execution. 
			 *  @param t Thread object to be started.
			 *  @param pol Scheduling policy */
			static void start(Thread *t, const SchedPolicy pol);
			static void start(Thread &t, const SchedPolicy pol);
			/** Runs a Background function in a dedicated Thread of execution.
			 *  \param bf The BackgroundFunction to be runned.
			 *  \param waitfor If true the start method wont return until the thread has been succesfully started. */
			static UInt64 start(BackgroundFunction &bf, bool waitfor = true);
			/** Tells wheter the t is running or not.
			 *  \param t The thread to be verified. */
			static bool isRunning(Thread *t);
			/** Returns the currently running Thread Object or 0 if the method is called from a non-Thread.*/
			static Thread *getCurrentThread();
			static BackgroundFunction *getCurrentBackgroundFunction();
			/** Returns the numeric id of the currently running Thread */
			static const UInt64 getCurrentThreadID();
			/** Returns how many threads are actively running. */
			static unsigned int activeCount();
			static UInt64 numericID(const Thread *t);
			static UInt64 numericID(const Thread &t);
			static void join(JoinableThread *t);
			static void join(JoinableThread &t);
			static void detach(JoinableThread *t);
			static void detach(JoinableThread &t);
			static Threading::SchedPolicy getSchedulingPolicy(Thread *t);
			static Threading::SchedPolicy getSchedulingPolicy(Thread &t);
			static void setSchedulingPolicy(Thread *t, Threading::SchedPolicy pol);
			static void setSchedulingPolicy(Thread &t, Threading::SchedPolicy pol);
			static void setSchedulingParams(Thread *t, Threading::SchedPolicy pol, int prio);
			static void setSchedulingParams(Thread &t, Threading::SchedPolicy pol, int prio);
			static void setPriority(Thread *t, int prio);
			static void setPriority(Thread &t, int prio);

			/** Tells if the current thread has been subclassed from the Thread
			 *  class */
			static bool currentIsThread();
			/** Tells if the current thread has been subclassed from the
			 *  BackgroundFunction class */
			static bool currentIsBackgroundFunction();
			/** Tells if the current thread is the main thread, that is the main()
			 *  function. 
			 *  WARNING: this method won't diferentiate bewteen natively created
			 *  threads and the main() function. */
			static bool currentIsMain();

			/** Performs a test to see if the current thread has been asked to
			 *  be cancelled, if it already has, then the thread execution will
			 *  stop at this point.
			 *  When this event occurs no finalization callbacks will by run,
			 *  not even the onTerminate() handler, only the cancellation
			 *  callbacks will be run, so you must use these in order to 
			 *  perform any required housekeeping for your threads. */
			static void testCancellation();
	};

};

#endif
