/*
 * $Id$
 */
#include<xvr2/Container.h>
                                                                                
namespace xvr2{
	namespace Util {
		Container::Container(){
#if GCC_MAJOR_VERSION < 3
			setClassName(xvr2::_xvr2Container);
#endif
			num_data = 0;
		}
	
		Container::Container(const char *s){
#if GCC_MAJOR_VERSION < 3
			setClassName(s);
#endif
			num_data = 0;
		}
	};
};

