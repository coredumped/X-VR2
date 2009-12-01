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
#ifndef __XVR2_NET_HTTP_CLIENT_H__
#define __XVR2_NET_HTTP_CLIENT_H__
#include<xvr2/String.h>
#include<xvr2/Net/TCPSocket.h>
#include<xvr2/Net/HTTPResponse.h>

namespace xvr2 {
	namespace Net {
		/** Handles HTPP client connections, implements the
		 *  GET, PUT, POST and DELETE methods, very useful
		 *  with RESTful web services. */
		class HTTPClient : public TCPSocket {
			private:
			protected:
				String url;
				String uagent;
			public:
				HTTPClient();
				HTTPClient(const String &_url);
				HTTPClient(const String &_url, const String &user_agent);
				static HTTPClient create(const String &url);
				static void mGet(const String &url, HTTPResponse &resp);
				void mGet(HTTPResponse &resp);
				void mPut(HTTPResponse &resp);
				void mPost(HTTPResponse &resp);
				void mDelete(HTTPResponse &resp);
				void runMethod(const String &method_name, const String &url, HTTPResponse &resp);
		};
	}
}


#endif
