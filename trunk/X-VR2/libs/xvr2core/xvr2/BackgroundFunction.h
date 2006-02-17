/*
 * $Id$
 */
#ifndef __XVR2_BACKGROUND_FUNCTION_H__
#define __XVR2_BACKGROUND_FUNCTION_H__
#include<xvr2/Function.h>
#include<xvr2/SharedVar.h>

namespace xvr2 {
	/** \class BackgroundFunction BackgroundFunction.h <xvr2/BackgroundFunction.h>
	 *  \brief
	 *  Interface class for functions which are run in the packground as a separate
	 *  thread subprocess. */
	class BackgroundFunction:public Function {
		protected:
		public:
			/** Tells wheter the function has been called already, it moves from
			 *  false to true just once in the lifetime of a BackgroundFunction.
			 *  You should never modify its value. */
			SharedVar<bool> called;
			SharedVar<bool> terminated;
			/** Default constructor, it does nothing. */
			BackgroundFunction(){
#ifdef USE_ENBEDDED_CLASSNAMES
				setClassName(_xvr2BackgroundFunction);
#endif
				called = false;
				terminated = false;
			}
			/** Destructor that destroys nothing. */
			virtual ~BackgroundFunction(){}
			/** Default functor function, in fact this method is the one to be
			 *  run in the background, please override it in your implementation
			 *  classes. */
			virtual void operator()(void) = 0;
	};
};

#endif
