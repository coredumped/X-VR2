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
#ifndef __XVR2_HASH_MAP_H__
#define __XVR2_HASH_MAP_H__
#ifdef __GNUC__
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>
#include<xvr2/Mutex.h>
#include<ext/hash_map>

namespace xvr2 {

	/** @brief X-VR2 HashMap, don't use yet, is not very portable,, for now it
	 *  only works with GNU C++ library. */
	template <class _Key, 
				class _Tp, 
				class _HashFcn, 
				class _EqualKey, 
				class _Alloc
				>
	class HashMap : public xvr2::Object , 
		public __gnu_cxx::hash_map<_Key, _Tp, _HashFcn, _EqualKey, _Alloc> {
		private:
		protected:
			xvr2::Mutex hmm;
		public:
			HashMap():
				__gnu_cxx::hash_map<_Key,_Tp,_HashFcn,_EqualKey,_Alloc>() { }
			HashMap(size_t n):
				__gnu_cxx::hash_map<_Key,_Tp,_HashFcn,_EqualKey,_Alloc>(n) { }
			template <class _InputIterator>
			HashMap(_InputIterator f, _InputIterator l):
				__gnu_cxx::hash_map<_Key,_Tp,_HashFcn,_EqualKey,_Alloc>(f, l){ }
			template <class _InputIterator>
			HashMap(_InputIterator f, _InputIterator l, size_t n):
				__gnu_cxx::hash_map<_Key,_Tp,_HashFcn,_EqualKey,_Alloc>(f, l, n){ }
			
			void lock(){
				hmm.lock();
			}
			
			void unlock(){
				hmm.unlock();
			}
	};
}
#else
#warning This system doesnt support the HashMap classes
#endif

#endif
