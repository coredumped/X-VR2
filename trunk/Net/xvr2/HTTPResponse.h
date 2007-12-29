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
#ifndef __XVR2_NET_HTTP_RESPONSE_H__
#define __XVR2_NET_HTTP_RESPONSE_H__
#include<xvr2/String.h>
#include<xvr2/Timestamp.h>

namespace xvr2 {
	namespace Net {
	
		class HTTPResponse : public xvr2::Object {
			private:
			protected:
				int _code;
				String _status;
				String _version;
				Timestamp _recvDate;
				String _srv;
				String _etag;
				String _clength;
				String _ctype;
			public:
				HTTPResponse();
		};
	
	}
}


#endif
