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
#include"StreamException.h"
#include<cerrno>

namespace xvr2 {

	StreamException::StreamException():SystemException(){}
	StreamException::StreamException(int c):SystemException(c){}

	StreamIsNotFlushable::StreamIsNotFlushable():StreamException(){}
	StreamIsNotFlushable::StreamIsNotFlushable(int c):StreamException(c){}

	StreamIsNotSeekable::StreamIsNotSeekable():StreamException(){}
	StreamIsNotSeekable::StreamIsNotSeekable(int c):StreamException(c){}
}

