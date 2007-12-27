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
#ifndef __XVR2_NET_URI_H__
#define __XVR2_NET_URI_H__
#include<xvr2/String.h>
#include<xvr2/Map.h>

namespace xvr2 {

	namespace Net {
	
		/** Uniform Resource Identifier class. Use when in need to break
		 *  down a URI's components. */
		class URI : public Object {
			private:
				/** Will parse the contents of _uri in order to obtain all
				 *  its components. */
				void parse();
			protected:
				String _uri;
				String _authority;
				String _scheme;
				String _user;
				String _password;
				String _host; 
				int _port;
				String _path;
				struct _cmpf {
					bool operator()(String &a, String &b){
						return strcmp(a.toCharPtr(), b.toCharPtr()) < 0;
					}
				};
				Map<String, String, _cmpf> param;
			public:
				URI();
				URI(const String &uri);
				~URI();
				const String &scheme();
				const String &scheme() const;
				const String &host();
				const String &host() const;
				int port();
				const String &path();
				const String &path() const ;
				const String parameterValue(const String &name);
				virtual std::string toString();
		};
	
	}

}

#endif /*URI_H_*/
