/* $Id$ */
#include"SystemException.h"
#include<cerrno>
#include<cstring>

#ifndef XVR2_ERRNO_DESCRIPTION_MAXLEN
#define XVR2_ERRNO_DESCRIPTION_MAXLEN 1024
#endif

namespace xvr2 {
	SystemException::SystemException(int _code){
		char buf[XVR2_ERRNO_DESCRIPTION_MAXLEN];
		if(_code == 0){
			_err_code = errno;
		}
		else{
			_err_code = _code;
		}
		strerror_r(_err_code, buf, XVR2_ERRNO_DESCRIPTION_MAXLEN);
		_err_str = buf;
	}
	
	int SystemException::code(){
		return _err_code;
	}
	
	const String &SystemException::message(){
		return _err_str;
	}
};
