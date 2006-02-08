/*
 * $Id$
 */
#include<xvr2/MemoryException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Memory::Memory(){
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
