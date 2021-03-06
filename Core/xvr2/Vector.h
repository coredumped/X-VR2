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
#ifndef __XVR2_VECTOR_H__
#define __XVR2_VECTOR_H__
#include<xvr2/Mutex.h>
#include<xvr2/String.h>
#include<vector>

namespace xvr2 {

	/** @brief Same as std::vector, but including some exclusive features
	 *  from X-VR2.
	 *  You may use this class in the same way you use std::vector, in fact
	 *  you don't need to use it at all, but bear in mind something, the 
	 *  standard std::vector class does not include some methods added here
	 *  like Vector::toString() or Vector::lock() and Vector::unlock()
	 *  @todo Document xvr2::Vector classes. */
	template<typename _Tp, typename _Alloc=std::allocator<_Tp> >
	class Vector : public xvr2::Object, public std::vector<_Tp, _Alloc> {
		protected:
			Mutex mv;
		public:
			/** @brief Builds a Vector from a range. */
			template<typename _InputIterator> 
			Vector (_InputIterator __first, 
						_InputIterator __last, 
						const _Alloc &__a = _Alloc()
					) : std::vector<_InputIterator>(__first, __last, __a){ }
			/** @brief Copy constructor, builds a vector from another. */
			Vector (const Vector &__x) : std::vector<_Tp, _Alloc>(__x){ }
			/** @brief Instantites a fixed size vector. */
			Vector (size_t __n,	const _Tp &__value = _Tp(), 
					const _Alloc &__a = _Alloc()
					) : 
					std::vector<_Tp, _Alloc>(__n, __value, __a){ }
			/** @brief Instantiates a Vector object with the given allocator. */
			Vector (const _Alloc &__a = _Alloc()) : 
					std::vector<_Tp, _Alloc>(__a){ }
			
			/** @brief Converts the items list to an understadable array. */
			std::string toString(){
				std::string ret;
				ret = "{ ";
				/*for(size_t i = 0; i < this->size(); i++){
					String item;
					item = this->at(i);
					if(i > 0){
						ret.append(",");
					}
					ret.append(item);
				}*/
				ret.append(" }");
				return std::string(ret);
			}
			/** @brief Restricts access from another thread to whatever
			 *  operations you're doing here look at: xvr2::Mutex::lock().
			 *  If for some reason you need to share this Vector between
			 *  multiple threads you should make use of the provided locking
			 *  mechanism to serialize read/write access. That being said
			 *  you should call lock() first, then perform whatever you need
			 *  to do with the Vector and finally call unlock(). */
			void lock(){
				mv.lock();
			}
			/** @brief Reenables access to other threads, this is the exact
			 *  opposite of Vector::lock.
			 *  @see Vector::lock */
			void unlock(){
				mv.unlock();
			}
	};
	
}

#endif
