/*
 * $Id$
 */
#ifndef __XVR2_SEMAPHORE_H__
#define __XVR2_SEMAPHORE_H__

#include<xvr2/Threading.h>
#include<xvr2/CoreExceptions.h>
#ifdef USE_POSIX_THREADS
#include<semaphore.h>
#endif

namespace xvr2{
	/**
	 * This class implements mutual exclusion semaphore objects
	 *
	 */
	class Semaphore:public Threading{
		private:
#ifdef USE_POSIX_THREADS
			sem_t __sem;
#endif
		protected:
			void init(int x);
			void destroy();
		public:
			Semaphore(int x);
			~Semaphore();
			void wait();
			void trywait();
			void post();
			void getvalue(int *x);
			void debugmsg(Semaphore *obj, const char *msg);
	};
};

#endif
