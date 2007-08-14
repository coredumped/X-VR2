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
#ifndef __XVR2_FUNCTION_H__
#define __XVR2_FUNCTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/Object.h>

namespace xvr2 {
	/** \class Function Function.h <xvr2/Function.h>
	 *  \brief
	 *  Interface class for implementing object functions */
	class Function:public Object {
		private:
		protected:
		public:
			/** Default constructor */
			Function();
	};
};

#endif
