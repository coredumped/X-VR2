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
#include<xvr2/Object.h>
#include<xvr2/Threading.h>
#include<xvr2/Mutex.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2{
	/**
	 * \class Thread Thread.h <xvr2/Thread.h>
	 * \version $Revision: 326 $
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
	 * 	SumBase *t0;
	 * 	SumBase *t1;
	 * 	SumBase *t2;
	 * 	SumBase *t3;
	 * 	t0 = new SumBase (100000, 199999);
	 * 	t1 = new SumBase (200000, 299999);
	 * 	t2 = new SumBase (300000, 399999);
	 * 	t3 = new SumBase (400000, 499999);
	 * 	t0->start();
	 * 	t1->start();
	 * 	t2->start();
	 * 	t3->start();
	 * 	while(ThreadManager::activeCount() > 0){
	 * 		//Wait until all calculations are complete.
	 * 		sleep(1);
	 * 	}
	 * 	cout << "total: " << t0->getTotal() +  t1->getTotal() +  t2->getTotal() +  t3->getTotal() << endl;
	 * }
	 * \endcode
	 */
	class	Thread:public	Threading{
		private:
	#ifdef	GNU_PTH
			/** Thread identifier this one is used when 
			 *  GNU Pth has been activated */
			pth_t thread;
	#else
			/** Thread identifier this one is used when 
			 *  GNU Pth has been activated */
			pthread_t thread;
	#endif
			friend class ThreadManager;
		protected:
			bool detached;
			/** This method detaches the thread from the 
			 *  current running program */
			void detach();
			int policy;
			int priority;
		public:
			/*void getAttrs(pthread_attr_t *tt){
				tt = &t_attr;
			}*/
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
			unsigned long int start();
			/** Call this method when you want to start running 
			 *  your thread, however please note that everytime 
			 *  you call this method, the thread will be
			 *  spawned again as a totally new instance. */
			unsigned long int start(void *arg);
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
			bool isRunning();
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
			unsigned long int numericID();
			unsigned long int numericID() const ;

			/**
			 * Waits for this thread to finish successfully joining the
			 * calling thread with this one. */
			void *join();
			bool joinable();
	};	

};

#endif
