/*
 * $Id$
 */
#ifndef __XVR2_JOINABLE_THREAD_H__
#define __XVR2_JOINABLE_THREAD_H__
#include<xvr2/Thread.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {
	class JoinableThread : public Thread {
		public:
			JoinableThread();
	};
};

#endif
