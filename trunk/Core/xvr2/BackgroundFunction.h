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
#ifndef __XVR2_BACKGROUND_FUNCTION_H__
#define __XVR2_BACKGROUND_FUNCTION_H__
#include<xvr2/Function.h>
#include<xvr2/FinalizerCallback.h>
#include<xvr2/SharedVar.h>
#include<xvr2/ThreadFinalizator.h>

namespace xvr2 {
	/** @class BackgroundFunction BackgroundFunction.h <xvr2/BackgroundFunction.h>
	 *  @brief Interface class for functions which are to be ran in the 
	 *  background as a separate thread subprocess. */
	class BackgroundFunction:public Function, public ThreadFinalizator {
		protected:
		public:
			UInt64 id;
			/** Tells wheter the function has been called already, it moves from
			 *  false to true just once in the lifetime of a BackgroundFunction.
			 *  You should never modify its value. */
			SharedVar<bool> called;
			SharedVar<bool> terminated;
			/** Default constructor, it does nothing. */
			BackgroundFunction();
			/** Destructor that destroys nothing. */
			virtual ~BackgroundFunction();
			/** Default functor function, in fact this method is the one to be
			 *  run in the background, please override it in your implementation
			 *  classes. */
			virtual void operator()(void) = 0;
			/** Routine to be called when the BackgroundFunction is about to be called
			 *  (before it starts) */
			virtual void onStart();
			/** Routine to be called after the BackgroundFunction has finished */
			virtual void onTerminate();
			/** Allows to register a callback function which will be called after the
			 *  BackgroundFunction terminates, in fact, it runs after the onTerminate()
			 *  method. */
			//void registerFinalizer(FinalizerCallback *fc);
			/** Executes all finalzers in reverse registration order deleting each one
			 *  after execution. */
			//void callFinalizers();
	};
};

#endif
