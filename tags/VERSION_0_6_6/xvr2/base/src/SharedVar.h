/*
 * $Id$
 */
#ifndef __SHARED_VAR_H__
#define __SHARED_VAR_H__
#include<Mutex.h>


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
#ifndef USING_GCC3
				setClassName(_xvr2SharedVar);
#endif
			}
			/**This constructor initializes the value of the shared variable */
			SharedVar(T v){
#ifndef USING_GCC3
				setClassName(_xvr2SharedVar);
#endif
				setValue(v);
			}
			/** Increases the shared variable's value in one unit*/
			T operator++(int XXX = 0){
				T u= 0;
				lock();
				u = var;
				u++;
				var = u;
#ifdef USE_DEBUG
				debugmsg(this, "Increasing ");
				std::cout << var << std::endl;
#endif
				unlock();
				return u;
			}
			/** Decreases the shared variable's value in one unit*/
			T operator--(int XXX = 0){
				T u= 0;
				lock();
				u = var;
				u--;
				var = u;
#ifdef USE_DEBUG
				debugmsg(this, "Decreasing ");
				std::cout << var << std::endl;
#endif
				unlock();
				return u;
			}
	};
};

#endif

