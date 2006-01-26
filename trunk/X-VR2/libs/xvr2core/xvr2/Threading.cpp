/*
 * $Id$
 */
#include"config.h"
#include "Threading.h"

namespace xvr2{

	Threading::Threading(){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Threading);
#endif
	}

}
