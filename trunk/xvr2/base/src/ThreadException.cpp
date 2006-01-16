/*
 * $Id$
 */
#include<xvr2/ThreadException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception{

		Thread::Thread(){
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
};


