/*
 * $Id$
 */
#include"config.h"
#include "ThreadException.h"
#include "MessageStrings.h"

namespace xvr2 {
	ThreadException::ThreadException(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ThreadException);
#endif
		description = (char *)xvr2::excepGenThread;
	}

	ThreadNotRunning::ThreadNotRunning(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ThreadNotRunningException);
#endif
		description = (char *)xvr2::excepThreadNotRunning;
	}


	ConditionVarWaitTimedOut::ConditionVarWaitTimedOut(){
#if __GNUC__ < 3
		setClassName((char *)xvr2::_xvr2ConditionVarWaitTimedOutException);
#endif
		description = (char *)xvr2::excepConditionVarWaitTimedOut;
	}
};


