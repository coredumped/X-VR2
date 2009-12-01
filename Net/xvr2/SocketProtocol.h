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
#ifndef __XVR2_NET_SOCKET_PROTOCOL_H__
#define __XVR2_NET_SOCKET_PROTOCOL_H__
#include<xvr2/String.h>
#include<vector>

namespace xvr2 {
	namespace Net {

		/** \class SocketProtocol SocketProtocol.h <xvr2/Net/SocketProtocol.h>
		 *
		 */
		class SocketProtocol : public Object {
			private:
				static void loadProtocols();
			protected:
				int _id;
				String _name;
				std::vector<String> _aliases;
				SocketProtocol(int i, const String &n);
				void addAlias(const String &a);
			public:
				SocketProtocol();
				SocketProtocol(const SocketProtocol &sp);
				int id();
				const String &name();
				const String &name() const;
				const std::vector<String> &aliases() const;
				const std::vector<String> &aliases();
				static const std::vector<SocketProtocol> &protocols();
				static SocketProtocol &protocol(int __id);
		};
	};
};

#endif

