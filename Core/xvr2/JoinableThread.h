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
#ifndef __XVR2_JOINABLE_THREAD_H__
#define __XVR2_JOINABLE_THREAD_H__
#include<xvr2/Thread.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {
	/** Implements joinable threads.
	 *  A joinable thread is a type of thread which must be awaited by another
	 *  thread after its completion, in order to release resources or to have
	 *  a computation result back. */
	class JoinableThread : public Thread {
		public:
			/** Mandatory constructor. */
			JoinableThread();
	};
}

#endif
