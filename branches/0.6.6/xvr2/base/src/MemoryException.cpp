/*
 * $Id$
 */
#include<MemoryException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Memory::Memory(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2MemoryException);
#endif
			description = (char *)xvr2::excepMemory;
		}

		AllocationFailed::AllocationFailed(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2AllocationFailedException);
#endif
			description = (char *)xvr2::excepAllocationFailed;
		}

		ReallocFailed::ReallocFailed(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ReallocFailedException);
#endif
			description = (char *)xvr2::excepReallocFailed;
		}

	};
};

