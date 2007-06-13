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
#ifndef strerror
			description = (char *)xvr2::excepGenIO;
#else
			description = strerror(errno);
#endif
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

	};
};

