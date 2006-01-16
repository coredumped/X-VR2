/*
 * $Id$
 */
#include<xvr2/MutexException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Mutex::Mutex(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2MutexException);
#endif
			description = (char *)xvr2::excepGenMutex;
		}

		DeadLock::DeadLock(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DeadLockException);
#endif
			description = (char *)xvr2::excepDeadLock;
		}

		UnableToLockMutex::UnableToLockMutex(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2UnableToLockMutexException);
#endif
			description = (char *)xvr2::excepMutexNoLock;
		}

		UnableToUnlockMutex::UnableToUnlockMutex(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2UnableToUnlockMutexException);
#endif
			description = (char *)xvr2::excepMutexNoUnlock;
		}

	};
};

