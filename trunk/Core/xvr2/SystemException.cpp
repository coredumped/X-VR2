/*
 * $Id$
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#include"SystemException.h"
#include"Memory.h"
#include"MessageStrings.h"
#include<cerrno>
#include<cstring>
#ifndef _WIN32
#include<dlfcn.h>
#endif

#ifndef XVR2_ERRNO_DESCRIPTION_MAXLEN
#define XVR2_ERRNO_DESCRIPTION_MAXLEN 512
#endif

namespace xvr2 {
	SystemException::SystemException(){
		os_errno = errno;
	}

	SystemException::SystemException(OSErrorCodeT error_code){
		if(error_code == 0){
			os_errno = errno;
		}
		else{
			os_errno = error_code;
		}
	}

	SystemException::SystemException(const SystemException &se){
		os_errno = se.os_errno;
	}

	OSErrorCodeT SystemException::osErrorCode(){
		return os_errno;
	}

#if !defined(_GNU_SOURCE) && ( _XOPEN_SOURCE == 600 || _POSIX_C_SOURCE == 200112L)
	static const String __undoc_err = "An undocumented error ocurred.";
#endif

	String SystemException::osErrorMessage(){
		char buf[XVR2_ERRNO_DESCRIPTION_MAXLEN];
//#if _XOPEN_SOURCE = 600 || _POSIX_C_SOURCE=200112L
#if !defined(_GNU_SOURCE) && ( _XOPEN_SOURCE == 600 || _POSIX_C_SOURCE == 200112L)
		if(strerror_r(os_errno, buf, XVR2_ERRNO_DESCRIPTION_MAXLEN) == -1){
			return __undoc_err;
		}
#else
		strerror_r(os_errno, buf, XVR2_ERRNO_DESCRIPTION_MAXLEN);
#endif
		return String(buf);
	}
	
	int SystemException::code(){
		return os_errno;
	}
	
	String SystemException::message(){
		char buf[XVR2_ERRNO_DESCRIPTION_MAXLEN];
		strerror_r(code(), buf, XVR2_ERRNO_DESCRIPTION_MAXLEN);
		return String(buf);
	}
	IOException::IOException(){
#ifndef strerror
		description = (char *)xvr2::excepGenIO;
#else
		description = strerror(errno);
#endif
	}

	IOException::IOException(OSErrorCodeT error_code):SystemException(error_code){
		description = (char *)xvr2::excepGenIO;
	}


///////////////////////////////////////
/////// DSOException //////////////////
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

	DSOSymbolException::DSOSymbolException(){
#ifdef _WIN32
		description = (char *)xvr2::excepNoLoadSymbol;
#else
		description = dlerror();
#endif
	}
	ElementNotFound::ElementNotFound(){
		description = (char *)xvr2::excepNoElem;
	}


///////////////////////////////////////
/////// FileException //////////////////
	FileException::FileException(){
		description = (char *)xvr2::excepFile;
	}
	FileException::FileException(OSErrorCodeT error_code):IOException(error_code){
		description = (char *)xvr2::excepFile;
	}

	BrokenPipe::BrokenPipe(){
		description = (char *)xvr2::excepBrokenPipe;
	}

	ProcOutOfFileDescriptors::ProcOutOfFileDescriptors(){
		description = (char *)xvr2::excepNoFptrs;
	}

	SysOutOfFileDescriptors::SysOutOfFileDescriptors(){
		description = (char *)xvr2::excepSysNoFptrs;
	}

	DeviceOrFIFONotFound::DeviceOrFIFONotFound(){
		description = (char *)xvr2::excepDeviceOrFIFONotFound;
	}

	DeviceNotFound::DeviceNotFound(){
		description = (char *)xvr2::excepDeviceNotFound;
	}

	InterruptedSystemCall::InterruptedSystemCall(){
		description = (char *)xvr2::excepInterruptedSystemCall;
	}

	SocketUnableToWrite::SocketUnableToWrite(){
		description = (char *)xvr2::excepSendFailed;
	}

	SocketUnableToRead::SocketUnableToRead(){
		description = (char *)xvr2::excepRecvFailed;
	}

}
