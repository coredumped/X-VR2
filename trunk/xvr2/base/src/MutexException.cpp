/*
 * $Id$
 */
#include<MutexException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Mutex::Mutex(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2MutexException);
#endif
			description = (char *)xvr2::excepGenMutex;
		}

		DeadLock::DeadLock(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DeadLockException);
#endif
			description = (char *)xvr2::excepDeadLock;
		}

		UnableToLockMutex::UnableToLockMutex(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UnableToLockMutexException);
#endif
			description = (char *)xvr2::excepMutexNoLock;
		}

		UnableToUnlockMutex::UnableToUnlockMutex(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UnableToUnlockMutexException);
#endif
			description = (char *)xvr2::excepMutexNoUnlock;
		}

	};
};

