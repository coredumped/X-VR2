/*
 * $Id$
 */
#ifndef __XVR2_DETACHED_THREAD_H__
#define __XVR2_DETACHED_THREAD_H__
#include<xvr2/Thread.h>

namespace xvr2 {
	class DetachedThread : public Thread {
		public:
			/** Instantiates a thread which will be run in detached state. */
			DetachedThread();
	};
};
#endif
