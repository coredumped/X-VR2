/*
 * $Id$
 *
 * X-VR2
 *
 * Copyright (C) Juan V. Guerrero 2008
 *
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#include<xvr2/Thread.h>
#include<xvr2/ThreadManager.h>
#include<xvr2/FileLogger.h>
#include<xvr2/SharedVar.h>
#include<xvr2/Timestamp.h>
#include<iostream>

xvr2::FileLogger logger;

class Work : public xvr2::Thread {
	private:
		xvr2::SharedVar<int> val;
		UInt32 steps;
		xvr2::SharedVar<bool> keep_working;
	public:
		Work(){
			val = 0;
			steps = 2;
			keep_working = true;
		}

		Work(int _steps){
			val = 0;
			steps = _steps;
			keep_working = true;
		}

		void terminate(){
			keep_working = false;
		}

		void operator()(){
			bool kw = keep_working.getValue();
			while(kw){
				val = val.getValue() + 1;
				logger << "val=" << val.getValue() << xvr2::NL;
				usleep(250000);
				kw = keep_working.getValue();
			}
		}

		int value(){
			return val.getValue();
		}
};

int main(){
	logger.open("fl_output.txt");
	Work w1(1), w2(1);
	logger << "Starting threads..." << xvr2::NL;
	w1.start();
	w2.start();
	std::cout << "Working (just wait 10 secs)...";
	std::cout.flush();
	for(int i = 0; i < 10; i++){
		logger << "w1=" << w1.value() << ",w2=" << w2.value() << xvr2::NL;
		sleep(1);
		if(!w1.started()){
			std::cerr << "Thread w1 has not started yet!!!!" << std::endl;
			return 1;
		}
	}
	w1.terminate();
	w2.terminate();
	std::cout << "\rWaiting for workers to finish..." << std::endl;
	while(!w1.terminated() || !w2.terminated()){
		usleep(100);
	}
	return 0;
}
