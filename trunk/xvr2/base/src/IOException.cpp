/*
 * $Id$
 */
#include<xvr2/IOException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		IO::IO(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2IOException);
#endif
#ifndef strerror
			description = (char *)xvr2::excepGenIO;
#else
			description = strerror(errno);
#endif
		}

		BrokenPipe::BrokenPipe(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2BrokenPipeException);
#endif
			description = (char *)xvr2::excepBrokenPipe;
		}

		ProcOutOfFileDescriptors::ProcOutOfFileDescriptors(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ProcOutOfFileDescriptorsException);
#endif
			description = (char *)xvr2::excepNoFptrs;
		}

		SysOutOfFileDescriptors::SysOutOfFileDescriptors(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2SysOutOfFileDescriptorsException);
#endif
			description = (char *)xvr2::excepSysNoFptrs;
		}

		DeviceOrFIFONotFound::DeviceOrFIFONotFound(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DeviceOrFIFONotFoundException);
#endif
			description = (char *)xvr2::excepDeviceOrFIFONotFound;
		}

		DeviceNotFound::DeviceNotFound(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DeviceNotFoundException);
#endif
			description = (char *)xvr2::excepDeviceNotFound;
		}

		InterruptedSystemCall::InterruptedSystemCall(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2InterruptedSystemCallException);
#endif
			description = (char *)xvr2::excepInterruptedSystemCall;
		}

		SocketUnableToWrite::SocketUnableToWrite(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2SocketUnableToWriteException);
#endif
			description = (char *)xvr2::excepSendFailed;
		}

		SocketUnableToRead::SocketUnableToRead(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2SocketUnableToReadException);
#endif
			description = (char *)xvr2::excepRecvFailed;
		}

	};
};

