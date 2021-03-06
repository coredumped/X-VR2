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
#include"config.h"
#include"Object.h"
#include"Thread.h"
#include"ThreadManager.h"
#include<pthread.h>
#include<errno.h>
#if __GNUC__ >= 3
#include<vector>
#else
#include<vector.h>
#endif
#include"Vector.h"
#include"Mutex.h"
#include"Map.h"

namespace xvr2 {
	void *runMethod(void *tx);
	void *runMethod_bf(BackgroundFunction &bf);

	class __thArgs2_t{
		public:
			Thread *thread;
			void   *arg;
			__thArgs2_t(){;}
			__thArgs2_t(Thread *thread_x, void *arg_x){
				thread = thread_x;
				arg = arg_x;
			}
	} ;

	class __ThreadData_t {
		public:
			__ThreadData_t(){
				policy = 0;
				priority = 0;
			}
#ifdef USE_POSIX_THREADS
			__ThreadData_t(pthread_t t, pthread_attr_t a, Thread *p, int pol){
				thread = t;
				attr = a;
				ptr = p;
				policy = pol;
			}
			pthread_t thread;
			pthread_attr_t attr;
			Thread *ptr;
			int policy;
			int priority;
#else
#error Currently POSIX threads are the only supported concurrency method
#endif
	};
	static xvr2::Vector<__ThreadData_t *> activeThreads;
	static xvr2::Vector<BackgroundFunction *> activeBFs;
	static Mutex lm;

#ifdef USE_POSIX_THREADS
	static Threading::SchedPolicy __from_posix(int i){
		Threading::SchedPolicy v;
		switch(i){
			case SCHED_RR:
				v = Threading::ROUND_ROBIN;
				break;
			case SCHED_FIFO:
				v = Threading::FIFO;
				break;
			default:
				v = Threading::NORMAL;
		}
		return v;
	}
	static int __to_posix(int i){
		int v;
		switch(i){
			case Threading::ROUND_ROBIN:
				v = SCHED_RR;
				break;
			case Threading::FIFO:
				v = SCHED_FIFO;
				break;
			default:
				v = SCHED_OTHER;
		}
		return v;
	}
#endif

	void __addThread(__ThreadData_t *info){
		activeThreads.lock();
		activeThreads.push_back(info);
		activeThreads.unlock();
	}
	void __removeThread(__ThreadData_t *info){
		unsigned int i;
		activeThreads.lock();
		for(i = 0; i < activeThreads.size(); i++){
			if(info == activeThreads[i]){
				activeThreads.erase(activeThreads.begin() + i);
			}
		}
		activeThreads.unlock();
	}

	static void _addBF(BackgroundFunction *bf){
		lm.lock();
		activeBFs.push_back(bf);
		lm.unlock();
	}
	static void _removeBF(BackgroundFunction *bf){
		unsigned long int i;
		BackgroundFunction *tx;
		lm.lock();
		for(i = 0; i < activeBFs.size(); i++){
			tx = activeBFs[i];
			if(tx == bf){
				activeBFs.erase(activeBFs.begin() + i);
			}
		}
		lm.unlock();
	}

	struct _x_ucmp {
		bool operator()(UInt64 a, UInt64 b) const{
			return (a < b)?true:false;
		}
	};

	xvr2::Map<UInt64, Thread *, _x_ucmp> __TRefs;

	/*static __ThreadData_t *findThread(const Thread *t){
		unsigned int i;
		__ThreadData_t *ret = 0;
		lm.lock();
		for(i = 0; i < activeThreads.size(); i++){
			if(activeThreads[i]->ptr == t){
				ret = activeThreads[i];
				break;
			}
		}
		lm.unlock();
		return ret;
	}*/

	static UInt64 __getThreadId(const Thread *t){
		UInt64 ret = 0;
		__TRefs.lock();
		xvr2::Map<UInt64, Thread *, _x_ucmp>::iterator iter;
		for(iter = __TRefs.begin(); iter != __TRefs.end(); iter++){
			if(iter->second == t){
				ret = iter->first;
				break;
			}

		}
		__TRefs.unlock();
		return ret;
	}

#ifdef USE_POSIX_THREADS
	/*void *runMethod(void *tx){
		__ThreadData_t *info;
		info = (__ThreadData_t *)tx;
		pthread_getschedparam(info->thread, &info->policy, (struct sched_param *)&info->priority);
		__addThread(info); //Add the thread to the thread list
		info->ptr->_started = true;
		info->ptr->run();
		info->ptr->callFinalizers();
		info->ptr->_terminated = true;
		__removeThread(info); //Remove thread from the thread list
		delete info;
		return 0;
	}*/

	void *runMethod_ref(Thread &tx){
		__TRefs.lock();
		__TRefs[ThreadManager::getCurrentThreadID()] = &tx;
		__TRefs.unlock();
		tx._started = true;
		tx();
		tx.callFinalizers();
		__TRefs.lock();
		__TRefs.erase(ThreadManager::getCurrentThreadID());
		__TRefs.unlock();
		tx._terminated = true;
		return 0;
	}
#endif

	void bf_cancellation_remover(void *arg){
		BackgroundFunction *bf = (BackgroundFunction *)arg;
		//Since we're being cancelled then just run all cancellation
		//cleanup handlers
		bf->callCancellationCallbacks();
		bf->terminated = true;
		_removeBF(bf);
	}

	void *runMethod_bf(BackgroundFunction &bf){
		_addBF(&bf);
		bf.called = true;
		bf.onStart();
#ifdef USE_POSIX_THREADS
		pthread_cleanup_push(bf_cancellation_remover, (void *)&bf);
#endif
		bf();
		ThreadManager::testCancellation();
		bf.onTerminate();
		bf.callFinalizers();
		_removeBF(&bf);
		bf.terminated = true;
#ifdef USE_POSIX_THREADS
		pthread_cleanup_pop(0);
#endif
		bf.removeCancellationCBs();
		return 0;
	}

	/*void ThreadManager::start(Thread *t){
		int pol;
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_getschedpolicy(&attr, &pol);
		if(t->joinable()){
#ifdef USE_POSIX_THREADS
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
#endif
		}
		else{
#ifdef USE_POSIX_THREADS
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
#endif
		}
		__ThreadData_t *info;
#ifdef USE_POSIX_THREADS
		info = new __ThreadData_t(thread, attr, t, pol);
#endif
		if(pthread_create(&thread, &attr, runMethod, info) == EAGAIN){
			throw ThreadNotRunning();
		}
		while(info->ptr->_started == false) System::usleep(100);
	}*/

	void ThreadManager::start(Thread &t){
#ifdef USE_POSIX_THREADS
		int pol;
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_getschedpolicy(&attr, &pol);
		t.schedPolicy == __from_posix(pol);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		if(pthread_create(&thread, &attr, (void* (*)(void*))runMethod_ref, (void *)&t) == EAGAIN){
			throw ThreadNotRunning();
		}
		while(t._started == false) usleep(100);
#else
#error Unable to build thread support for this platform
#endif
	}

	static const char *_iparm = "Policy";

	void ThreadManager::start(Thread &t, Threading::SchedPolicy pol){
		int err_code;
		t.schedPolicy = pol;
#ifdef USE_POSIX_THREADS
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		err_code = pthread_attr_setschedpolicy(&attr, __to_posix(pol));
#endif
		if(err_code != 0){
			if(err_code == ENOTSUP)
				throw SecurityException();
			else
				throw InvalidParameter(_iparm);
		}
#ifdef USE_POSIX_THREADS
		if(t.joinable()){
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		}
		else{
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		}
		if(pthread_create(&thread, &attr, (void* (*)(void*))runMethod_ref, (void *)&t) == EAGAIN){
			throw ThreadNotRunning();
		}
		while(t._started == false) usleep(100);
#endif

	}

	UInt64 ThreadManager::start(BackgroundFunction &bf, bool waitfor){
#ifdef USE_POSIX_THREADS
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		bf.id = (UInt64)thread;
		if(pthread_create(&thread, &attr, (void* (*)(void*))runMethod_bf, (void *)&bf) == EAGAIN){
			throw ThreadNotRunning();
		}
		if(waitfor){
			while(bf.called == false) System::usleep(100);
		}
		return (UInt64)thread;
#endif
	}

	bool ThreadManager::isRunning(Thread *t){
		return t->running();
	}

	unsigned int ThreadManager::activeCount(){
		unsigned int n;
		lm.lock();
		n = activeThreads.size() + activeBFs.size();
		lm.unlock();
		return n;
	}

	Thread *ThreadManager::getCurrentThread(){
		Thread *ret = 0;
		__TRefs.lock();
		ret = __TRefs[getCurrentThreadID()];
		__TRefs.unlock();
		return ret;
	}

	const UInt64 ThreadManager::getCurrentThreadID(){
#ifdef USE_POSIX_THREADS
		return (UInt64)pthread_self();
#endif
	}

	BackgroundFunction *ThreadManager::getCurrentBackgroundFunction(){
		BackgroundFunction *ret = 0;
		lm.lock();
		for(UInt32 i = 0; i < activeBFs.size(); i++){
			if(getCurrentThreadID() == activeBFs[i]->id){
				ret = activeBFs[i];
				break;
			}
		}
		lm.unlock();
		return ret;
	}

	void ThreadManager::setPriority(Thread *t, int prio){
#ifdef USE_POSIX_THREADS
			UInt64 tid = __getThreadId(t);
			pthread_setschedparam(tid, __to_posix(t->schedPolicy.getValue()), (sched_param *)&prio);
#endif
	}

	void ThreadManager::setPriority(Thread &t, int prio){
		ThreadManager::setPriority(&t, prio);
	}

	UInt64 ThreadManager::numericID(const Thread *t){
		return __getThreadId(t);
	}

	UInt64 ThreadManager::numericID(const Thread &t){
		return ThreadManager::numericID(&t);
	}

	void ThreadManager::join(JoinableThread *t){
#ifdef USE_POSIX_THREADS
		pthread_join(__getThreadId(t), 0);
#else
#error Currently POSIX threads are the only supported concurrency method
#endif
	}

	void ThreadManager::join(JoinableThread &t){
		ThreadManager::join(&t);
	}
	void ThreadManager::detach(JoinableThread *t){
#ifdef USE_POSIX_THREADS
		pthread_detach(__getThreadId(t));
#endif
	}

	void ThreadManager::detach(JoinableThread &t){
		ThreadManager::detach(&t);
	}

	void ThreadManager::setSchedulingPolicy(Thread *t, Threading::SchedPolicy pol){
#ifdef USE_POSIX_THREADS
		int ret = 0;
		UInt64 tid = __getThreadId(t);
		ret = pthread_setschedparam(tid, __to_posix(pol), (struct sched_param *)&ret);
		if(ret == EINVAL){
			throw InvalidParameter(_iparm);
		}
		else if(ret == EPERM){
			throw SecurityException();
		}
		int newpol;
		int newprio;
		pthread_getschedparam(tid, &newpol, (struct sched_param *)&newprio);
		t->schedPolicy = __from_posix(newpol);
#endif
	}

	void ThreadManager::setSchedulingPolicy(Thread &t, Threading::SchedPolicy pol){
		ThreadManager::setSchedulingPolicy(&t, pol);
	}

	void ThreadManager::setSchedulingParams(Thread *t, Threading::SchedPolicy pol, int prio){
#ifdef USE_POSIX_THREADS
		UInt64 tid = __getThreadId(t);
		int ret;
		ret = pthread_setschedparam(tid, __to_posix(pol), (struct sched_param *)&prio);
		int newpol;
		int newprio;
		pthread_getschedparam(tid, &newpol, (struct sched_param *)&newprio);
		t->schedPolicy = __from_posix(newpol);
#endif
	}

	void ThreadManager::setSchedulingParams(Thread &t, Threading::SchedPolicy pol, int prio){
		ThreadManager::setSchedulingParams(&t, pol, prio);
	}

	Threading::SchedPolicy ThreadManager::getSchedulingPolicy(Thread *t){
		return (Threading::SchedPolicy)t->schedPolicy.getValue();
	}

	Threading::SchedPolicy ThreadManager::getSchedulingPolicy(Thread &t){
		return ThreadManager::getSchedulingPolicy(&t);
	}

//////////////////////////// THREAD IDENTIFICATION STUFF /////////////////////
	bool ThreadManager::currentIsThread(){
		if(getCurrentThread() == 0) return false;
		return true;
	}

	bool ThreadManager::currentIsBackgroundFunction(){
		if(getCurrentBackgroundFunction() == 0) return false;
		return true;
	}

	bool ThreadManager::currentIsMain(){
		bool ret = false;
		if(getCurrentThread() == 0 && getCurrentBackgroundFunction() == 0){
			ret = true;
		}
		return ret;
	}

	void ThreadManager::testCancellation(){
#ifdef USE_POSIX_THREADS
		pthread_testcancel();
#endif
	}
}
