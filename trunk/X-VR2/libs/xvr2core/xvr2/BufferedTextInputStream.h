/* $Id$ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
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
	};
};

#endif

