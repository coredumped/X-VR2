/*
 * $Id$
 */
#include<IOException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		IO::IO(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2IOException);
#endif
#ifndef strerror
			description = (char *)xvr2::excepGenIO;
#else
			description = strerror(errno);
#endif
		}

		BrokenPipe::BrokenPipe(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2BrokenPipeException);
#endif
			description = (char *)xvr2::excepBrokenPipe;
		}

		ProcOutOfFileDescriptors::ProcOutOfFileDescriptors(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ProcOutOfFileDescriptorsException);
#endif
			description = (char *)xvr2::excepNoFptrs;
		}

		SysOutOfFileDescriptors::SysOutOfFileDescriptors(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SysOutOfFileDescriptorsException);
#endif
			description = (char *)xvr2::excepSysNoFptrs;
		}

		DeviceOrFIFONotFound::DeviceOrFIFONotFound(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DeviceOrFIFONotFoundException);
#endif
			description = (char *)xvr2::excepDeviceOrFIFONotFound;
		}

		DeviceNotFound::DeviceNotFound(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DeviceNotFoundException);
#endif
			description = (char *)xvr2::excepDeviceNotFound;
		}

		InterruptedSystemCall::InterruptedSystemCall(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2InterruptedSystemCallException);
#endif
			description = (char *)xvr2::excepInterruptedSystemCall;
		}

		SocketUnableToWrite::SocketUnableToWrite(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SocketUnableToWriteException);
#endif
			description = (char *)xvr2::excepSendFailed;
		}

		SocketUnableToRead::SocketUnableToRead(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SocketUnableToReadException);
#endif
			description = (char *)xvr2::excepRecvFailed;
		}

	};
};

