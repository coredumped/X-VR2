/*
 * $Id$
 */
#include"config.h"
#include"MutexException.h"
#include"MessageStrings.h"

namespace xvr2 {
	namespace Exception{

		MutexException::MutexException(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2MutexException);
#endif
			description = (char *)xvr2::excepGenMutex;
		}

		DeadLock::DeadLock(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2DeadLockException);
#endif
			description = (char *)xvr2::excepDeadLock;
		}

		UnableToLockMutex::UnableToLockMutex(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2UnableToLockMutexException);
#endif
			description = (char *)xvr2::excepMutexNoLock;
		}

		UnableToUnlockMutex::UnableToUnlockMutex(){
#if __GNUC__ < 3
			setClassName((char *)xvr2::_xvr2UnableToUnlockMutexException);
#endif
			description = (char *)xvr2::excepMutexNoUnlock;
		}

	};
};

