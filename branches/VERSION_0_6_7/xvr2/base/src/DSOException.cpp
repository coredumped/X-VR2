/*
 * $Id$
 */
#include<DSOException.h>
#include<MessageStrings.h>
#include<errno.h>
#ifndef _WIN32
#include<dlfcn.h>
#endif

namespace xvr2 {
	namespace Exception{

		DSO::DSO(const char *msg){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DSOException);
#endif
			if(msg)
				description = (char *)msg;
			else
				description = (char *)xvr2::excepGenDSO;
		}

		CantLoadDSO::CantLoadDSO(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2CantLoadDSOException);
#endif
#ifdef _WIN32		
			description = (char *)xvr2::excepNoLoadDSO;
#else
			description = dlerror();
#endif
		}

		CantUnloadDSO::CantUnloadDSO(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2CantUnloadDSOException);
#endif
#ifdef _WIN32		
			description = (char *)xvr2::excepNoUnloadDSO;
#else
			description = dlerror();
#endif
		}

		DSOSymbol::DSOSymbol(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DSOSymbolException);
#endif
#ifdef _WIN32
			description = (char *)xvr2::excepNoLoadSymbol;
#else
			description = dlerror();
#endif
		}

	};
};

