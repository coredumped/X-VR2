/*
 * $Id$
 */
#include"config.h"
#include"AutomatedGC.h"
#include<unistd.h>

namespace xvr2{

	AutomatedGC::AutomatedGC(UInt32 speriod){
		_scanperiod = speriod;
		keepscanning = false;
	}

	void AutomatedGC::run(){
		while(keepscanning){
			System::usleep(_scanperiod * 1000);
			collect();
		}
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
