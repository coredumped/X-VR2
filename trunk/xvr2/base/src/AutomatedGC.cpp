/*
 * $Id$
 */
#include<xvr2/AutomatedGC.h>
#include<unistd.h>

namespace xvr2{

	AutomatedGC::AutomatedGC(UInt32 speriod){
#if __GNUC__ < 3
		Thread::setClassName(xvr2::_xvr2AutomatedGC);
#endif
		_scanperiod = speriod;
		keepscanning = false;
	}

	void *AutomatedGC::run(){
		while(keepscanning){
			System::usleep(_scanperiod * 1000);
			collect();
		}
		return 0;
	}

	void AutomatedGC::startChecking(){
		keepscanning = true;
		start();
	}

	void AutomatedGC::stop(){
		keepscanning = false;
	}
	/*AutomatedGC::(){
	AutomatedGC::(){
	AutomatedGC::(){*/
};
