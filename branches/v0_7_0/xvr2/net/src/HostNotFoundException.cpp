/*
 * $Id$
 */
#include<xvr2/HostNotFoundException.h>
#include<xvr2/MessageStrings.h>
namespace xvr2 {
	namespace Exception{

		HostNotFound::HostNotFound(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2HostNotFoundException);
#endif
			description = (char *)xvr2::excepHostNotFound;
		}

	};
};

