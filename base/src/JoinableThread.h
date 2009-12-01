/*
 * $Id$
 */
#ifndef __XVR2_JOINABLE_THREAD_H__
#define __XVR2_JOINABLE_THREAD_H__
#include<xvr2/Thread.h>

namespace xvr2 {
	class JoinableThread : public Thread {
		public:
			JoinableThread();
	};
};

#endif
