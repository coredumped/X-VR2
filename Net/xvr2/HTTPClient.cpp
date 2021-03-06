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
#include"xvr2config.h"
#include"HTTPClient.h"
#include"HTTPResponse.h"

namespace xvr2 {
	namespace Net {
#ifdef USING_LIBCURL
		HTTPClient::HTTPClient(){
			
		}
		
		HTTPClient::HTTPClient(const String &url){
			
		}
#else
#error Native HTTPClient classes not implemented yet, please use the libcurl backend
#endif
	}
}
