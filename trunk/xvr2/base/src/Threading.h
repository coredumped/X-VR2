/*
 * $Id$
 */
#ifndef __XVR2_THREADING_H__
#define __XVR2_THREADING_H__
#include<System.h>
#include<ThreadException.h>

namespace xvr2{
	/**
	 * This class is an interface for all Threading classes
	 */
	class Threading:public System{
		public:
			/** Default Constructor, remember that this class
			 * is just an interface */
			Threading();
	};
}

#endif

