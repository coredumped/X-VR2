#include<Threading.h>

namespace xvr2{

	Threading::Threading(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Threading);
#endif
	}

}
