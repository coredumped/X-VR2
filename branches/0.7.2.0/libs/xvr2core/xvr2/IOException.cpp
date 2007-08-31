/*
 * $Id$
 */
#include"config.h"
#include"xvr2config.h"
#include"IOException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		IOException::IOException(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2IOException);
#endif
#ifndef strerror
			description = (char *)xvr2::excepGenIO;
#else
			description = strerror(errno);
#endif
		}

		BrokenPipe::BrokenPipe(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2BrokenPipeException);
#endif
			description = (char *)xvr2::excepBrokenPipe;
		}

		ProcOutOfFileDescriptors::ProcOutOfFileDescriptors(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2ProcOutOfFileDescriptorsException);
#endif
			description = (char *)xvr2::excepNoFptrs;
		}

		SysOutOfFileDescriptors::SysOutOfFileDescriptors(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2SysOutOfFileDescriptorsException);
#endif
			description = (char *)xvr2::excepSysNoFptrs;
		}

		DeviceOrFIFONotFound::DeviceOrFIFONotFound(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2DeviceOrFIFONotFoundException);
#endif
			description = (char *)xvr2::excepDeviceOrFIFONotFound;
		}

		DeviceNotFound::DeviceNotFound(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2DeviceNotFoundException);
#endif
			description = (char *)xvr2::excepDeviceNotFound;
		}

		InterruptedSystemCall::InterruptedSystemCall(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2InterruptedSystemCallException);
#endif
			description = (char *)xvr2::excepInterruptedSystemCall;
		}

		SocketUnableToWrite::SocketUnableToWrite(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2SocketUnableToWriteException);
#endif
			description = (char *)xvr2::excepSendFailed;
		}

		SocketUnableToRead::SocketUnableToRead(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2SocketUnableToReadException);
#endif
			description = (char *)xvr2::excepRecvFailed;
		}

	};
};

