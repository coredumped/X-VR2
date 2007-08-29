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
	 * @todo Document the Semaphore class plz
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
	};
};

#endif
