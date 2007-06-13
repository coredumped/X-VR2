/*
 * $Id$
 */
#include"config.h"
#include "ThreadException.h"
#include "MessageStrings.h"

namespace xvr2 {
	ThreadException::ThreadException(){
		description = (char *)xvr2::excepGenThread;
	}

	ThreadNotRunning::ThreadNotRunning(){
		description = (char *)xvr2::excepThreadNotRunning;
	}


	ConditionVarWaitTimedOut::ConditionVarWaitTimedOut(){
		description = (char *)xvr2::excepConditionVarWaitTimedOut;
	}
};


