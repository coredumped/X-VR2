/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/Container.h>
#ifdef USE_EMBEDDED_CLASSNAMES
#include<xvr2/_xvr2utilClassNames.h>
#endif
                                                                                
namespace xvr2{
	namespace Util {
		Container::Container(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_Container);
#endif
			num_data = 0;
		}
	
		Container::Container(const char *s){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName(__xvr2_Util_Container);
#endif
			num_data = 0;
		}
	};
};
