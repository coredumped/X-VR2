/*
 * $Id$
 */
#include"config.h"
#include"MemoryException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		MemoryException::MemoryException(){
			description = (char *)xvr2::excepMemory;
		}

		AllocationFailed::AllocationFailed(){
			description = (char *)xvr2::excepAllocationFailed;
		}

		ReallocFailed::ReallocFailed(){
			description = (char *)xvr2::excepReallocFailed;
		}

	};
};

