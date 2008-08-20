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

#include<xvr2/CoreExceptions.h>
#include<xvr2/InvalidParameterException.h>
#include<xvr2/Threading.h>
#include<xvr2/Thread.h>
#include<xvr2/JoinableThread.h>
#include<xvr2/BackgroundFunction.h>

namespace xvr2 {

	/** @class ThreadManager ThreadManager.h <xvr2/ThreadManager.h>
	 *  @brief This class brings basic thread creation management functions,
	 *  and permits running tasks concurrently. */
	class ThreadManager:public Threading {
		private:
		protected:
		public:
			/** Initiates execution of the given Thread object.
			 *  @param t Thread to be started */
			static void start(Thread &t);
			/** Initiates execution of the given Thread object with the given
			 *  scheduling policy.
			 *  @param t Thread object to be started.
			 *  @param pol Scheduling policy */
			static void start(Thread &t, const SchedPolicy pol);
			/** Runs a Background function in a dedicated Thread of execution.
			 *  @param bf The BackgroundFunction to be runned.
			 *  @param waitfor If true the start method wont return until the
			 *  thread has been succesfully started. */
			static UInt64 start(BackgroundFunction &bf, bool waitfor = true);
			/** Tries to see if the given thread is running.
			 *  @param t The thread to be verified.
			 *  @return true if it is running, false otherwise. */
			static bool isRunning(Thread *t);
			/** @brief Returns the currently running Thread object.
			 *  @return A pointer to the currently running Thread Object or 0
			 *  if the method is called from a non-Thread object.*/
			static Thread *getCurrentThread();
			/** @brief Returns the currently running BackgroundFunction object.
			 *  @return A pointer to the currently running Thread Object or 0
			 *  if the method is called from a non-Thread object.*/
			static BackgroundFunction *getCurrentBackgroundFunction();
			/** @brief Obtains the numeric identification of the current
			 *  threaded task.
			 *  @note The returned id will match to the id given by the POSIX
			 *  pthread implementation.
			 *  @returns The numeric id of the currently running Thread or
			 *  BackgroundFunction. */
			static const UInt64 getCurrentThreadID();
			/** @brief Obtains a count of the currently running concurrent
			 *  tasks.
			 *  @returns how many Thread or BackgroundFunction objects are
			 *  concurrently running. */
			static unsigned int activeCount();
			/** @brief Obtains the numeric of the given Thread object.
			 *  @note This numeric id will match the POSIX's assigned one.
			 *  @param t The Thread object.
			 *  @return The concurrent task numeric id. */
			static UInt64 numericID(const Thread *t);
			/** @brief Obtains the numeric of the given Thread object.
			 *  @note This numeric id will match the POSIX's assigned one.
			 *  @param t The Thread object.
			 *  @return The concurrent task numeric id. */
			static UInt64 numericID(const Thread &t);
			/** @brief Tells the current task to "join" the specified
			 *  JoinableThread.
			 *  Joining is a thread operation in which the current thread is
			 *  blocked until another thread finishes.
			 *  @param t The JoinableThread object, which is the thread we will
			 *  be expecting to finish in order to continue. */
			static void join(JoinableThread *t);
			/** @brief Tells the current task to "join" the specified
			 *  JoinableThread.
			 *  Joining is a thread operation in which the current thread is
			 *  blocked until another thread finishes.
			 *  @param t The JoinableThread object, which is the thread we will
			 *  be expecting to finish in order to continue. */
			static void join(JoinableThread &t);
			/** @brief Tells the given thread that no one with expecting it to
			 *  finish.
			 *  This method will change the thread's execution to a detached
			 *  state, that is, inmediately after the thread finishes, release
			 *  all allocated resources from memory since nobody will ever care
			 *  to joining it.
			 *  @param t The thread we want to have running in a detached
			 *  state. */
			static void detach(JoinableThread *t);
			/** @brief Tells the given thread that no one with expecting it to
			 *  finish.
			 *  This method will change the thread's execution to a detached
			 *  state, that is, inmediately after the thread finishes, release
			 *  all allocated resources from memory since nobody will ever care
			 *  to joining it.
			 *  @param t The thread we want to have running in a detached
			 *  state. */
			static void detach(JoinableThread &t);
			/** Obtains the scheduling policy in use by the given thread.
			 *  @param t A Thread object whose information you want to know.
			 *  @return The scheduling policy in use by the Thread. */
			static Threading::SchedPolicy getSchedulingPolicy(Thread *t);
			/** Obtains the scheduling policy in use by the given thread.
			 *  @param t A Thread object whose information you want to know.
			 *  @return The scheduling policy in use by the Thread. */
			static Threading::SchedPolicy getSchedulingPolicy(Thread &t);
			/** Allows to change a Thread scheduling policy.
			 *  @param t A Thread object whose policy you want to change. */
			static void setSchedulingPolicy(Thread *t, Threading::SchedPolicy pol);
			/** Allows to change a Thread scheduling policy.
			 *  @param t A Thread object whose policy you want to change. */
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
			 *  @warning this method won't diferentiate between natively created
			 *  threads and the main() function. */
			static bool currentIsMain();

			/** @brief Performs a test to see if the current thread has been
			 *  asked to be cancelled.
			 *  When this event occurs no finalization callbacks will by run,
			 *  not even the onTerminate() handler, only the cancellation
			 *  callbacks will be run, so you must use these in order to
			 *  perform any required housekeeping for your threads. */
			static void testCancellation();
	};

}


#endif
