/*
 * $Id$
 */
#include"config.h"
#include"MutexException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		MutexException::MutexException(){
			description = (char *)xvr2::excepGenMutex;
		}

		DeadLock::DeadLock(){
			description = (char *)xvr2::excepDeadLock;
		}

		UnableToLockMutex::UnableToLockMutex(){
			description = (char *)xvr2::excepMutexNoLock;
		}

		UnableToUnlockMutex::UnableToUnlockMutex(){
			description = (char *)xvr2::excepMutexNoUnlock;
		}

	};
};

