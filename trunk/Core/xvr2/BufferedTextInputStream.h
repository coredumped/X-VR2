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
#ifndef __XVR2_BUFFERED_TEXT_INPUT_STREAM_H__
#define __XVR2_BUFFERED_TEXT_INPUT_STREAM_H__
#include<xvr2/String.h>
#include<xvr2/StreamInterface.h>
#include<xvr2/RawInputStream.h>

namespace xvr2 {

	class BufferedTextInputStream : public RawInputStream {
		protected:
			UInt32 _bufsize;
			String buffer;
			String _lterm;
		public:
			BufferedTextInputStream();
			BufferedTextInputStream(RawInputStream &input, const String &__lterm = NL);
			void open(RawInputStream &input, const String &__lterm = NL);
			~BufferedTextInputStream();
			//virtual UInt32 read(void *data, UInt32 size);
			void operator>>(String &s);
			static void setDefaultBufferSize(UInt32 _size);
			void setBufferSize(UInt32 _size);
			/** Returns the amount of remaining bytes to be read */
			UInt32 remaining();
	};
};

#endif

