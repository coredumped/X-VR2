/*
 * $Id$
 */
#ifndef __XVR2_SHARED_VAR_H__
#define __XVR2_SHARED_VAR_H__
#include<xvr2/Mutex.h>
#include<xvr2/CoreExceptions.h>


namespace xvr2{

	/**
	 * This class is define template to implemented Shared varibles*/
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
#if __GNUC__ < 3
				setClassName(_xvr2SharedVar);
#endif
			}
			/**This constructor initializes the value of the shared variable */
			SharedVar(T v){
#if __GNUC__ < 3
				setClassName(_xvr2SharedVar);
#endif
				//setValue(v);
				var = v;
			}
			/** Increases the shared variable's value in one unit*/
			T operator++(int){
				T u= 0;
				lock();
				u = var;
				u++;
				var = u;
				unlock();
				return u;
			}
			/** Decreases the shared variable's value in one unit*/
			T operator--(int){
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
};

#endif