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
#ifndef __XVR2_STREAM_EXCEPTION_H__
#define __XVR2_STREAM_EXCEPTION_H__
#include<xvr2/String.h>
#include<xvr2/SystemException.h>

namespace xvr2 {

	class StreamException : public SystemException {
		public:
			StreamException();
			StreamException(int c);
	};

	class StreamIsNotFlushable : public StreamException {
		public:
			StreamIsNotFlushable();
			StreamIsNotFlushable(int c);
	};

	class StreamIsNotSeekable : public StreamException {
		public:
			StreamIsNotSeekable();
			StreamIsNotSeekable(int c);
	};
};

#endif

