/*
 * $Id$
 */
#include"xvr2/Object.h"
#include"xvr2/Thread.h"
#include"xvr2/ThreadManager.h"
#include"xvr2/ThreadException.h"
#include<pthread.h>
#include<errno.h>
#include"xvr2/List.h"
#include"xvr2/Mutex.h"

namespace xvr2 {

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

	static Util::List<Thread *> activeThreads;
	//static Util::List<unsigned long int> threadIDs;
	static Mutex lm;

	static Thread *findThread(unsigned long int id){
		unsigned int i;
		Thread *ret = 0, *t;
		lm.lock();
		for(i = 0; i < activeThreads.size(); i++){
			t = activeThreads.get(i);
			if(t->numericID() == id){
				ret = t;
				break;
			}
		}
		lm.unlock();
		return ret;
	}

	static Thread *findThread(Thread *t){
		unsigned int i;
		Thread *ret = 0;
		lm.lock();
		for(i = 0; i < activeThreads.size(); i++){
			if(activeThreads.get(i) == t){
				ret = activeThreads.get(i);
				break;
			}
		}
		lm.unlock();
		return ret;
	}

	void *ThreadManager::runMethod(void *tx){
		void *val;
		Thread *t;
		t = (Thread *)tx;
		addThread(t, pthread_self()); //Add the thread to the thread list
		val = t->run();
		removeThread(t, pthread_self()); //Remove thread from the thread list
		//delete t; //Temporarily commented out, please report any memory leaks
		return val;
	}

	void *ThreadManager::runMethod_arg(void *tx){
		void *val;
		__thArgs2_t *targs;
		targs = (__thArgs2_t *)tx;
		addThread(targs->thread, pthread_self()); //Add the thread to the thread list
		val = targs->thread->run(targs->arg);
		removeThread(targs->thread, pthread_self()); //Remove thread from the thread list
		delete targs->thread;
		return val;
	}

	unsigned long int ThreadManager::start(Thread *t){
		pthread_t thread;
		if(pthread_create(&thread, NULL, ThreadManager::runMethod, t) == EAGAIN){
			throw Exception::ThreadNotRunning();
		}
		return thread;
	}

	unsigned long int ThreadManager::start(Thread *t, void *arg){
		pthread_t thread;
		__thArgs2_t *targs;
		targs = new __thArgs2_t(t, arg);
		if(pthread_create(&thread, NULL, ThreadManager::runMethod_arg, (void *)targs) == EAGAIN){
			throw Exception::ThreadNotRunning();
		}
		return thread;
	}
	void ThreadManager::addThread(Thread *t, unsigned long int id){
		lm.lock();
		activeThreads.add(t);
		//threadIDs.add(id);
		lm.unlock();
	}
	void ThreadManager::removeThread(Thread *t, unsigned long int id){
		unsigned long int i;
		Thread *tx;
		lm.lock();
		for(i = 0; i < activeThreads.size(); i++){
			tx = activeThreads.get(i);
			if(tx->numericID() == id){
				//threadIDs.remove(i);
				activeThreads.remove(i);
			}
		}
		lm.unlock();
	}
	bool ThreadManager::isRunning(Thread *t){
		if(findThread(t))
			return true;
		return false;
	}
	unsigned int ThreadManager::activeCount(){
		unsigned int n;
		lm.lock();
		n = activeThreads.size();
		lm.unlock();
		return n;
	}
	const Thread *ThreadManager::getCurrentThread(){
		return findThread(pthread_self());
	}
	const unsigned long int ThreadManager::getCurrentThreadID(){
		return pthread_self();
	}
};
