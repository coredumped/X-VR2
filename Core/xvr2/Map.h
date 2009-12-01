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
#ifndef __XVR2_MAP_H__
#define __XVR2_MAP_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/Mutex.h>
#include<map>
 
namespace xvr2 {

	template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
            typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
	class Map : public xvr2::Object, public
		std::map<_Key, _Tp, _Compare, _Alloc> {
		private:
		protected:
			xvr2::Mutex mm;
		public:
			Map() : std::map<_Key, _Tp, _Compare, _Alloc>() { }
			
			
			void lock(){
				mm.lock();
			}
			void unlock(){
				mm.unlock();
			}
	};
}
 
#endif
