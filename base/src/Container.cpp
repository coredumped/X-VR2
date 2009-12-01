/*
 * $Id$
 */
#include<xvr2/Container.h>
                                                                                
namespace xvr2{
	namespace Util {
		Container::Container(){
#if __GNUC__ < 3
			setClassName(xvr2::_xvr2Container);
#endif
			num_data = 0;
		}
	
		Container::Container(const char *s){
#if __GNUC__ < 3
			setClassName(s);
#endif
			num_data = 0;
		}
	};
};

