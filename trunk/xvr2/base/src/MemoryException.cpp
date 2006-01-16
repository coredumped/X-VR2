/*
 * $Id$
 */
#include<xvr2/MemoryException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Memory::Memory(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2MemoryException);
#endif
			description = (char *)xvr2::excepMemory;
		}

		AllocationFailed::AllocationFailed(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2AllocationFailedException);
#endif
			description = (char *)xvr2::excepAllocationFailed;
		}

		ReallocFailed::ReallocFailed(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ReallocFailedException);
#endif
			description = (char *)xvr2::excepReallocFailed;
		}

	};
};

