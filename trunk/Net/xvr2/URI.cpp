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
#include "URI.h"
#include<xvr2/Tokenizer.h>

namespace xvr2 {

	namespace Net {

		URI::URI(){
		}
		
		URI::URI(const String &uri){
			_uri = uri;
			parse();
		}

		URI::~URI(){
		}
		
		static const char *_scheme_div = ":";

		std::string URI::toString(){
			return std::string(_uri);
		}

		const String &URI::scheme(){
			return _scheme;
		}

		const String &URI::scheme() const {
			return _scheme;
		}

		const String &URI::host(){
			return _host;
		}

		const String &URI::host() const {
			return _host;
		}

		int URI::port(){
			return _port;
		}

		const String &URI::path(){
			return _path;
		}

		const String &URI::path() const {
			return _path;
		}
		
		void URI::parse(){
			/*              hierarchycal-part
			 *          ____________|____________
			 *         /                         \
			 *   foo://example.com:8042/over/there?name=ferret#nose
      		 *   \_/   \______________/\_________/ \_________/ \__/
      		 *    |          |            |            |        |
      		 * scheme     authority     path          query   fragment
      		 *    |   ____________________|___
      		 *   / \ /                        \
      		 *   urn:example:animal:ferret:nose
      		 */
			size_t pos = 0;
			_scheme.clear();
			_authority.clear();
			_port = -1;
			_path.clear();
			param.clear();
			
			String hier_part;
			String non_hier_part;
			String __uri = _uri;
			
			pos = __uri.find(_scheme_div, 0);
			if(pos == __uri.npos){
				//Path is relative
				if(!__uri.startsWith("//")){
					__uri.insert(0, "//");
				}
				
			}
			else{
				_scheme = __uri.substr(0, pos + 1);
				__uri.biteLeft(pos + 1);
				//TODO: In case the port remains as -1 and we have a valid scheme perform a lookup to obtain the default port associated to such scheme.
			}
			
			if(__uri.startsWith("//")){
				//Might be an URL
				__uri.biteLeft(2);
				if(__uri.find('?', 0) != __uri.npos){
					xvr2::Tokenizer t1(__uri, "?");
					hier_part = t1.next();
					non_hier_part = t1.next();
				}
				else if(__uri.find('#', 0) != __uri.npos){
					xvr2::Tokenizer t1(__uri, "#");
					hier_part = t1.next();
					non_hier_part = t1.next();
				}
				else{
					hier_part = __uri;
				}
				String address;
				//Now we got hierachical and non-hierarchical parts
				//Process hierarchical part
				if((pos = hier_part.find('/')) != hier_part.npos){
					address = hier_part.substr(0, pos);
					hier_part.biteLeft(pos);
					_path = hier_part;
				}
				else{
					address = hier_part;
				}
				if(address.size() > 0){
					String hostinfo;
					if((pos = address.find('@', 0)) != address.npos){
						Tokenizer t2(address, "@");
						String authinfo = t2.next();
						hostinfo = t2.next();
						if((pos = authinfo.find(':', 0)) != address.npos){
							_user = authinfo;
						}
						else{
							Tokenizer t3(authinfo, ":");
							_user = t3.next();
							_password = t3.next();
						}
					}
					else{
						_user.clear();
						_password.clear();
						hostinfo = address;
					}
					if(hostinfo.size() > 0){
						if(hostinfo.find(':', 0) == address.npos){
							//Only has the ip_address or hostname
							_host = hostinfo;
						}
						else{
							//Has hostname plus port information
							Tokenizer t4(hostinfo, ":");
							_host = t4.next();
							String tmpp = t4.next();
							_port = tmpp.toInt();
						}
					}
				}
				
				
				//Process non-hierarchical part
			}
			else{
				//Might be an URN
			}
			
			
			
		}

	}

}
