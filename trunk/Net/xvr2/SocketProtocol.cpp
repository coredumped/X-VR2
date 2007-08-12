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
#include<xvr2/Mutex.h>
#include<netdb.h>
#include"SocketProtocol.h"
#include"NetworkExceptions.h"

namespace xvr2 {
	namespace Net {

		static const char *__xvr2_ip_proto_name = "ip";

		SocketProtocol::SocketProtocol(){
			_id = 0;
			_name = __xvr2_ip_proto_name;
			_aliases.push_back("IP");
		}

		SocketProtocol::SocketProtocol(int i, const String &n){
			_id = i;
			_name = n;
		}

		void SocketProtocol::addAlias(const String &a){
			_aliases.push_back(a);
		}

		SocketProtocol::SocketProtocol(const SocketProtocol &sp){
			_id = sp._id;
			_name = sp._name;
			_aliases = sp._aliases;
		}

		int SocketProtocol::id(){
			return _id;
		}

		const String &SocketProtocol::name(){
			return _name;
		}

		const String &SocketProtocol::name() const {
			return _name;
		}

		const std::vector<String> &SocketProtocol::aliases() const {
			return _aliases;
		}

		const std::vector<String> &SocketProtocol::aliases(){
			return _aliases;
		}

		static Mutex read_m;
		static std::vector<SocketProtocol> __all_p;

		void SocketProtocol::loadProtocols(){
			read_m.lock();
			if(__all_p.size() == 0){
				setprotoent(0);
				struct protoent *pro;
				while((pro = getprotoent()) != 0){
					SocketProtocol sp(pro->p_proto, pro->p_name);
					for(int i = 0; ; i++){
						if(pro->p_aliases[i] != 0){
							sp.addAlias(pro->p_aliases[i]);
						}
						else{
							break;
						}
					}
					__all_p.push_back(sp);
				}
			}
			read_m.unlock();
		}

		const std::vector<SocketProtocol> &SocketProtocol::protocols(){
			SocketProtocol::loadProtocols();
			return __all_p;
		}

		SocketProtocol &SocketProtocol::protocol(int __id){
			SocketProtocol::loadProtocols();
			UInt32 i = 0;
			for(i = 0; i < __all_p.size(); i++){
				if(__all_p[i].id() == __id) break;
			}
			if(i >= __all_p.size()){
				throw UnsupportedProtocol();
			}
			return __all_p[i];
		}
	};
};

