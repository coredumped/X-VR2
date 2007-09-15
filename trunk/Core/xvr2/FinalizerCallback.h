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
#ifndef __XVR2_FINALIZER_CALLBACK_H__
#define __XVR2_FINALIZER_CALLBACK_H__
#include<xvr2/Function.h>
#include<xvr2/String.h>

namespace xvr2{

	/** @todo Document the FinalizerCallback class */
	class FinalizerCallback : public Function {
		public:
			FinalizerCallback();
			virtual ~FinalizerCallback();
			virtual void operator()();
	};
}

#endif
