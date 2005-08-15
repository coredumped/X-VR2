/*
 * $Id$
 */
#ifndef __XVR2_NET_Crypto_EXCEPTION_H__
#define __XVR2_NET_Crypto_EXCEPTION_H__
#include<xvr2/Exception.h>

namespace xvr2 {
	namespace Exception{

		class Crypto:public Exception{
			public:
				/** Default constructor */
				Crypto();
		};

	};
};
#endif

