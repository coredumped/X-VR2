/*
 * $Id$
 */
#ifndef ___THREAD_H__
#define ___THREAD_H__

#ifdef USE_GNUPTH
#include<pth.h>
#else
	#include<pthread.h>
#endif
#include<Object.h>
#include<Threading.h>
#include<Mutex.h>

namespace xvr2{
	/**
	 * \class Thread
	 * \author Juan V. Guerrero
	 * \version $Revision$
	 * \brief
	 * This class encapsulates the thread library functionality using 
	 * POSIX-THREADS.\n
	 * In order to use this class you have to create a sub-class from
	 * it, then you have to override the run method and put there
	 * whatever code you want your program run concurrently.
	 * Example:
	 * \code
	 * #include<xvr2.h>
	 * 
	 * using namespace xvr2;
	 * using namespace std;
	 * class SumBase: public Thread {
	 * 	protected:
	 * 		int startnum;
	 * 		int endnum;
	 * 		int total;
	 * 	public:
	 * 		SumBase(int s, int e){
	 * 			startnum = s;
	 * 			endnum = e;
	 * 			total = 0;
	 * 		}
	 * 		void *run();
	 * 		int getStartnum(){
	 * 			return startnum;
	 * 		}
	 * 		int getEndnum(){
	 * 			return startnum;
	 * 		}
	 * 		int getTotal(){
	 * 			return total;
	 * 		}
	 * };
	 *
	 * void *SumBase::run(){
	 * 	total = 0;
	 * 	for(int i = startnum; i <= endnum; i++){
	 * 		total += i;
	 * 	}
	 * }
	 *
	 * void main(){
	 * 	SumBase t0(0, 99999);
	 * 	SumBase t1(100000, 199999);
	 * 	SumBase t2(200000, 299999);
	 * 	SumBase t3(300000, 399999);
	 * 	t0->start();
	 * 	t1->start();
	 * 	t2->start();
	 * 	t3->start();
	 * 	while(t0->isRunning() || t1->isRunning() || t2->isRunning() || t3->isRunning()){
	 * 		//Wait until all calculations are complete.
	 * 		sleep(1);
	 * 	}
	 * 	cout << "total: " << t0->getTotal() +  t1->getTotal() +  t2->getTotal() +  t3->getTotal() << endl;
	 * }
	 * \endcode
	 */
	class	Thread:public	Threading{
		private:
			/** This flag will say if this thread is 
			 *  running or not */
			bool _running;
			bool _haveargs;
	#ifdef	GNU_PTH
			/** Thread identifier this one is used when 
			 *  GNU Pth has been activated */
			pth_t thread;
			/**
			 * This is the wrapping function which calls the 
			 * run method so it can be executed as a thread, 
			 * for GNU Pth this function must return 
			 * a <b>void *</b>
			 */
			static void *runMethod(void *thethread);
	#else
			/** Thread identifier this one is used when 
			 *  GNU Pth has been activated */
			pthread_t thread;
			/**
			 * This member will hold the attributes for 
			 * the current thread
			 */
			pthread_attr_t t_attr;
			/** This is the wrapping function which calls 
			 *  the run method so it can be* executed as a 
			 *  thread, for GNU Pth this function must 
			 *  return an \b int */
			static void *runMethod(void *thethread);
			/** This is the wrapping function which calls 
			 *  the run method so it can be* executed as a 
			 *  thread, for GNU Pth this function must 
			 *  return an \b int.
			 *  \note This method will be call if a call to the
			 *  start() method had any parameters in it. Most commonly
			 *  this method will be called if this ois a 
			 *  multi-startable thread.\n
			 *  A multi-startable thread is a thread which might be
			 *  started any number of times, because of this it will
			 *  need to have its own data stack in order to be fully
			 *  reentrant */
			static void *runMethod_args(void *data_stack);
	#endif
		protected:
			/** This is a wrapper and is intended to be 
			 *  used only for derived classes */
			int _start();
			int _start(void *arg);
			/** This method detaches the thread from the 
			 *  current running program */
			void detach();
			int policy;
		public:
			/**
			 * Please use this set of constants to define or
			 * stablish a thread execution policy
			 */
			enum SchedPolicy{
				/** Default scheduling policy, 
				 *  non-realtime */
				NORMAL,
				/** Round Robin based realtime 
				 *  scheduling policy */
				ROUND_ROBIN,
				/** First In First Out based realtime 
				 *  scheduling policy */
				FIFO
			};
			/** 
			 * This variable is just for knowing if the thread 
			 * can be autodetached or no,* currently it 
			 * does nothing, but is here for backward 
			 * compatibility */
			bool autodetach;
			/** Default constructor */
			Thread();
			/** This is the class destructor, it simply 
			 *  calls detach for cleanup purposes */
			virtual ~Thread(){
				//killMe();
			}
			/** Call this method when you want to start running 
			 *  your thread, however please note that everytime 
			 *  you call this method, the thread will be
			 *  spawned again as a totally new instance. */
			int start();
			/** Call this method when you want to start running 
			 *  your thread, however please note that everytime 
			 *  you call this method, the thread will be
			 *  spawned again as a totally new instance. */
			int start(void *arg);
			/** <b>Very important</b>\n
			 * You must override this method so you can provide
			 * the thread process itself
			 * whatever you define this method does, in your 
			 * subclass is what the thread
			 * will start doing when you call start() */
			virtual void *run();
			/** <b>Very important</b>\n
			 * You must override this method so you can provide
			 * the thread process itself
			 * whatever you define this method does, in your 
			 * subclass is what the thread
			 * will start doing when you call start() */
			virtual void *run(void *arg);
			/** This method detaches the thread from the 
			 *  current running program, just like detach() does
			 */
			void killMe();
			/**
			 * Use this method to verify if your thread 
			 * is running; */
			bool isRunning(){
			  return _running;
			}
			/** This method will set the scheduling policy for 
			 *  the current thread, there are two types 
			 *  scheduling policies:\n
			 *  * Realtime\n
			 *  * Non-realtime\n
			 *  Realtime policies are: ROUND_ROBIN and FIFO\n
			 *  Non-realime is called NORMAL */
			void setSchedulingPolicy(SchedPolicy pol = NORMAL);

			/**
		         * Use this method to set the priority for the 
			 * current scheduling policy.  */
			void setPriority(int prio);
			
			/**
		         * This method will return a 32 bit integer 
			 * representing the current thread */
			static unsigned int numericID();
	};	

};

#endif
