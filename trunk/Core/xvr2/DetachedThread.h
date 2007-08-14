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
#ifndef __XVR2_DETACHED_THREAD_H__
#define __XVR2_DETACHED_THREAD_H__
#include<xvr2/Thread.h>
#include<xvr2/CoreExceptions.h>

namespace xvr2 {
	class DetachedThread : public Thread {
		public:
			/** Instantiates a thread which will be run in detached state. */
			DetachedThread();
	};
};
#endif
