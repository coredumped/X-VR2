/*
 * $Id$
 * 
 * This class encapsulates the thread library functionality through 
 * POSIX Threads and GNU Pth
 */
#ifdef USING_GCC3
#include<iostream>
#else
#include<iostream.h>
#endif
#include<errno.h>
#ifdef USE_GNUPTH
#include<pth.h>
#endif
#include<stdlib.h>
#include<errno.h>
#include<Thread.h>
#include<MessageStrings.h>

namespace xvr2{

	typedef struct {
		Thread *thread;
		void   *arg;
	} __thArgs_t;

#ifdef USE_DEBUG
	static bool __thMshow;
#endif

	Thread::Thread(){
#ifdef USE_DEBUG
		if(__thMshow){
#ifdef USE_POSIX_THREADS
			debugmsg(this, "Thread engine is compiled against current POSIX threads implementation\n");
#else
			debugmsg(this, "Thread engine is compiled against GNU Pth\n");
#endif
			__thMshow = true;
		}
#endif
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Thread);
#endif
		_running = false;
		policy = Thread::NORMAL;
	}

	int Thread::start(){
		Thread *t = this;
		int r;
#ifdef USE_GNUPTH
			thread = pth_spawn(PTH_ATTR_DEFAULT, runMethod, t);
#else
			pthread_attr_init(&t_attr);
			pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);
			pthread_create(&thread, &t_attr, runMethod, t);
#endif
		_running = true;
		return r;
	}

	int Thread::start(void *arg){
		__thArgs_t *t;
		int r;
		t         = new __thArgs_t();
		t->thread = this;
		t->arg    = arg;
		_haveargs = true;
#ifdef USE_GNUPTH
			thread = pth_spawn(PTH_ATTR_DEFAULT, runMethod, t);
#else
			pthread_attr_init(&t_attr);
			pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);
			pthread_create(&thread, &t_attr, runMethod_args, t);
#endif
		_running = true;
		return r;
	}

	void Thread::detach(){
#ifdef USE_DEBUG
		debugmsg(this, xvr2::msgDetachingThread);
#endif
#ifndef USE_GNUPTH
		pthread_detach(numericID());	
#endif
	}

	int Thread::_start(){
		int y;
		y = start();
#ifdef USE_GNUPTH
		void *rr;
		pth_join(thread, &rr);
#endif
		return y;
	}

	int Thread::_start(void *arg){
		int y;
		y = start(arg);
#ifdef USE_GNUPTH
		void *rr;
		pth_join(thread, &rr);
#endif
		return y;
	}

	void Thread::killMe(){
#ifdef USE_GNUPTH
		pth_cancel(thread);
#else
		pthread_exit(0x00);	
#endif
	}

#ifdef USE_SDL
	int Thread::runMethod_args(void *meptr){
#else
	void *Thread::runMethod_args(void *ds){
#endif
		__thArgs_t *data_stack;
		data_stack = (__thArgs_t *)ds;
		Thread *me = (Thread *)data_stack->thread;
#ifdef USE_DEBUG
		debugmsg(me, "starting a new parameterized thread\n");
#endif
		me->run(data_stack->arg);
#ifdef USE_GNUPTH
		return NULL;
#else
		return 0;
#endif
	}

#ifdef USE_SDL
	int Thread::runMethod(void *meptr){
#else
	void *Thread::runMethod(void *meptr){
#endif
		Thread *me = (Thread *)meptr;
#ifdef USE_DEBUG
		debugmsg(me, "starting a new thread\n");
#endif
		me->run();
#ifdef USE_GNUPTH
		return NULL;
#else
		return 0;
#endif
	}

	void *Thread::run(){
		debugmsg(this, xvr2::msgThreadOverride);
		return NULL;
	}

	void *Thread::run(void *arg){
		debugmsg(this, xvr2::msgThreadOverride);		
		return NULL;
	}

	void Thread::setSchedulingPolicy(SchedPolicy pol){
		if(isRunning()){
			throw Exception::ThreadNotRunning();
			return;
		}
		switch(pol){
			case Thread::ROUND_ROBIN:
				//This code will set the scheduling policy to round robin
				
#ifdef USE_POSIX_THREADS
					if(pthread_attr_setschedpolicy(&t_attr, SCHED_RR)){
						policy = pol;
					}
#endif
				break;
			case Thread::FIFO:
				//This code will set the scheduling policy to FIFO (First In First Out)
#ifdef USE_POSIX_THREADS
					if(pthread_attr_setschedpolicy(&t_attr, SCHED_FIFO)){
						policy = pol;
					}
#endif
				break;
			default:
				//This code will set the scheduling policy to NORMAL
#ifdef USE_POSIX_THREADS
					if(pthread_attr_setschedpolicy(&t_attr, SCHED_OTHER)){
						policy = pol;
					}
#else
					policy = pol;
#endif
		}
	}

	void Thread::setPriority(int prio){
#ifdef USE_POSIX_THREADS
			int pp;
			pp = prio;
			/*switch(policy){
				case FIFO:
					pthread_setschedparam(thread, SCHED_FIFO, (sched_)prio);
					break;
				case ROUND_ROBIN:
					pthread_setschedparam(thread, SCHED_RR, prio);
					break;
				default:
					pthread_setschedparam(thread, SCHED_OTHER, prio);
			}*/
			pthread_attr_setschedparam((pthread_attr_t *)&t_attr, (sched_param *)&pp);
#endif
}
	unsigned int Thread::numericID(){
#ifdef USE_POSIX_THREADS
		return pthread_self();
#else
		return pth_self();
#endif
	}
	
};
