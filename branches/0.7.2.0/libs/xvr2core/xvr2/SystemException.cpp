/* $Id$ */
#include"SystemException.h"
#include"Memory.h"
#include<cerrno>
#include<cstring>

#ifndef XVR2_ERRNO_DESCRIPTION_MAXLEN
#define XVR2_ERRNO_DESCRIPTION_MAXLEN 1024
#endif

namespace xvr2 {
	SystemException::SystemException(int _code){
		if(_code == 0){
			_err_code = errno;
		}
		else{
			_err_code = _code;
		}
	}
	
	int SystemException::code(){
		return _err_code;
	}
	
	String SystemException::message(){
		if(code() == 0){
			return String(_err_str);
		}
		char buf[XVR2_ERRNO_DESCRIPTION_MAXLEN];
#if _XOPEN_SOURCE == 600
		strerror_r(code(), buf, XVR2_ERRNO_DESCRIPTION_MAXLEN);
		return String(buf);
#else
		return String(strerror_r(code(), buf, XVR2_ERRNO_DESCRIPTION_MAXLEN));
#endif
	}
};
