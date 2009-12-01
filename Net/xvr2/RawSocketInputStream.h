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
#ifndef __XVR2_NET_RAW_SOCKET_INPUT_STREAM_H__
#define __XVR2_NET_RAW_SOCKET_INPUT_STREAM_H__
#include<xvr2/RawInputStream.h>
#include<xvr2/Net/NetworkExceptions.h>
#include<xvr2/Net/SocketExceptions.h>

namespace xvr2 {
	namespace Net {

		class RawSocketInputStream : public RawInputStream {
			protected:
				int flags;
			public:
				RawSocketInputStream();
				virtual ~RawSocketInputStream();
				RawSocketInputStream(int __fd);
				RawSocketInputStream(const String &fname);
				void open(int __fd);
				void open(const String &fname);
				virtual void close();
				void setFlags(int _f);

				virtual UInt32 read(void *data, UInt32 size);
				bool eof();
				virtual void seek(FileOffsetT _pos) throw(StreamIsNotSeekable);
				virtual void seekEnd() throw(StreamIsNotSeekable);
				virtual void seekBegin() throw(StreamIsNotSeekable);
				virtual void seekStep(FileOffsetT _step) throw(StreamIsNotSeekable);
		};
	};
};

#endif

