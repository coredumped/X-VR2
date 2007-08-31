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
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2DSOException);
#endif
		if(msg)
			description = (char *)msg;
		else
			description = (char *)xvr2::excepGenDSO;
	}

	CantLoadDSO::CantLoadDSO(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2CantLoadDSOException);
#endif
#ifdef _WIN32		
		description = (char *)xvr2::excepNoLoadDSO;
#else
		description = dlerror();
#endif
	}

	CantUnloadDSO::CantUnloadDSO(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2CantUnloadDSOException);
#endif
#ifdef _WIN32		
		description = (char *)xvr2::excepNoUnloadDSO;
#else
		description = dlerror();
#endif
	}

	DSOSymbol::DSOSymbol(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2DSOSymbolException);
#endif
#ifdef _WIN32
		description = (char *)xvr2::excepNoLoadSymbol;
#else
		description = dlerror();
#endif
	}
};

