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
#ifndef __XVR2_INVALID_PARAMETER_EXCEPTION_H__
#define __XVR2_INVALID_PARAMETER_EXCEPTION_H__
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>

namespace xvr2{
	/** \class InvalidParameter CoreExceptions.h <xvr2/CoreExceptions.h>
	 *  \brief This exception is thrown whenever you call a system call with
	 *  an invalid parameter. */
	class InvalidParameter:public Exception{
		private:
			String param_name;
		public:
			/** Default constructor */
			InvalidParameter();
			/** Use this constructor to specify the name of the faulty
			 *  parameter */
			InvalidParameter(const String &_param_name);
			/** Returns the name of the faulty parameter */
			const String &param();
	};
}

#endif
