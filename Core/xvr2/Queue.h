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
#ifndef __XVR2_QUEUE_H__
#define __XVR2_QUEUE_H__
#include<xvr2/Mutex.h>
#include<xvr2/String.h>
#include<queue>

namespace xvr2 {

	template<typename _Tp>
	class Queue : public xvr2::Object, public std::queue<_Tp> {
		private:
		protected:
			Mutex mq;
		public:
			Queue() : std::queue<_Tp>() { }
			
			void lock(){
				mq.lock();
			}
			
			void unlock(){
				mq.unlock();
			}
	};
}

#endif
