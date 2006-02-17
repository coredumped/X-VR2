/*
 * $Id$
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
#include"Mutex.h"

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

	//static Util::List<Thread *> activeThreads;
	static std::vector<Thread *> activeThreads;
	static std::vector<BackgroundFunction *> activeBFs;
	static Mutex lm;

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

	static Thread *findThread(unsigned long int id){
		unsigned int i;
		Thread *ret = 0, *t;
		lm.lock();
		for(i = 0; i < activeThreads.size(); i++){
			t = activeThreads[i];
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
			if(activeThreads[i] == t){
				ret = activeThreads[i];
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

	void *ThreadManager::runMethod_bf(BackgroundFunction &bf){
		_addBF(&bf);
		bf.called = true;
		bf();
		_removeBF(&bf);
		bf.terminated = true;
		return 0;
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
			throw ThreadNotRunning();
		}
		return thread;
	}

	unsigned long int ThreadManager::start(Thread *t, void *arg){
		pthread_t thread;
		__thArgs2_t *targs;
		targs = new __thArgs2_t(t, arg);
		if(pthread_create(&thread, NULL, ThreadManager::runMethod_arg, (void *)targs) == EAGAIN){
			throw ThreadNotRunning();
		}
		return thread;
	}

	unsigned long int ThreadManager::start(BackgroundFunction &bf, bool waitfor){
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		if(pthread_create(&thread, &attr, (void* (*)(void*))ThreadManager::runMethod_bf, (void *)&bf) == EAGAIN){
			throw ThreadNotRunning();
		}
		if(waitfor){
			while(bf.called == false) System::usleep(100);
		}
		return thread;
	}
	void ThreadManager::addThread(Thread *t, unsigned long int id){
		lm.lock();
		//activeThreads.add(t);
		activeThreads.push_back(t);
		lm.unlock();
	}
	void ThreadManager::removeThread(Thread *t, unsigned long int id){
		unsigned long int i;
		Thread *tx;
		lm.lock();
		for(i = 0; i < activeThreads.size(); i++){
			tx = activeThreads[i];
			if(tx->numericID() == id){
				activeThreads.erase(activeThreads.begin() + i);
				//TODO: Verify that no leaks remain after this
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
		n = activeThreads.size() + activeBFs.size();
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
