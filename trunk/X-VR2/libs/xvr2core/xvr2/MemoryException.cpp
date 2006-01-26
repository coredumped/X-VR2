/*
 * $Id$
 */
#include"config.h"
#include"MemoryException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		MemoryException::MemoryException(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2MemoryException);
#endif
			description = (char *)xvr2::excepMemory;
		}

		AllocationFailed::AllocationFailed(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2AllocationFailedException);
#endif
			description = (char *)xvr2::excepAllocationFailed;
		}

		ReallocFailed::ReallocFailed(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2ReallocFailedException);
#endif
			description = (char *)xvr2::excepReallocFailed;
		}

	};
};

