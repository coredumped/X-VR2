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
#ifndef __XVR2_SHARED_VAR_H__
#define __XVR2_SHARED_VAR_H__
#include<xvr2/Mutex.h>
#include<xvr2/CoreExceptions.h>


namespace xvr2{

	/**
	 * This class is define template to implemented Shared varibles.
	 * @todo Polish the SharedVar class docs. */
	template <class T> 
	class SharedVar:protected Mutex{
		private:
			/**T var is the shared variable*/
			T var;
		public:
			/**Returns the values of the shared var*/
			T getValue(T v = 0){
				lock();
				v = var;
				unlock();
				return v;
			}
			/**Changes shared valuble's value*/
			void setValue(T v = 0){
				lock();
				var = v;
				unlock();
			}
			/**Constructor that does nothing*/
			SharedVar(){
			}
			/**This constructor initializes the value of the shared variable */
			SharedVar(T v){
				//setValue(v);
				var = v;
			}
			/** Increases the shared variable's value in one unit*/
			T operator++(){
				T u= 0;
				lock();
				u = var;
				u++;
				var = u;
				unlock();
				return u;
			}
			/** Decreases the shared variable's value in one unit*/
			T operator--(){
				T u= 0;
				lock();
				u = var;
				u--;
				var = u;
				unlock();
				return u;
			}
			T operator=(T v){
				lock();
				var = v;
				unlock();
				return v;
			}
			bool operator==(T v){
				bool ret;
				lock();
				ret = (var==v)?true:false;
				unlock();
				return ret;
			}
			bool operator!=(T v){
				bool ret;
				lock();
				ret = (var==v)?false:true;
				unlock();
				return ret;
			}
	};
}

#endif
