/*
 * $Id$
 */
#include"config.h"
#include"DSOException.h"
#include"MessageStrings.h"
#include<errno.h>
#ifndef _WIN32
#include<dlfcn.h>
#endif

namespace xvr2 {
	DSOException::DSOException(const char *msg){
		if(msg)
			description = (char *)msg;
		else
			description = (char *)xvr2::excepGenDSO;
	}

	CantLoadDSO::CantLoadDSO(){
#ifdef _WIN32		
		description = (char *)xvr2::excepNoLoadDSO;
#else
		description = dlerror();
#endif
	}

	CantUnloadDSO::CantUnloadDSO(){
#ifdef _WIN32		
		description = (char *)xvr2::excepNoUnloadDSO;
#else
		description = dlerror();
#endif
	}

	DSOSymbol::DSOSymbol(){
#ifdef _WIN32
		description = (char *)xvr2::excepNoLoadSymbol;
#else
		description = dlerror();
#endif
	}
};

