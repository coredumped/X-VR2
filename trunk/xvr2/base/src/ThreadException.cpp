/*
 * $Id$
 */
#include<xvr2/ThreadException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Thread::Thread(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ThreadException);
#endif
			description = (char *)xvr2::excepGenThread;
		}

		ThreadNotRunning::ThreadNotRunning(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ThreadNotRunningException);
#endif
			description = (char *)xvr2::excepThreadNotRunning;
		}


		ConditionVarWaitTimedOut::ConditionVarWaitTimedOut(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ConditionVarWaitTimedOutException);
#endif
			description = (char *)xvr2::excepConditionVarWaitTimedOut;
		}

	};
};


