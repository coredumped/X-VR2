/*
 * $Id$
 *
 * X-VR2
 *
 * Copyright (C) Juan V. Guerrero 2007
 *
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#include"config.h"
#include"FileLogger.h"
#include<xvr2/Timestamp.h>
#include<xvr2/ThreadManager.h>

namespace xvr2{

	// Start definition of local variables
	// End definition of local variables

	// Start definition of local functions
	// End definition of local functions




	//Start implementation of class: FileLogger
	FileLogger::FileLogger(bool _show_times){
		show_times = _show_times;
	}

	FileLogger::FileLogger(const String &fname, bool _show_times){
		show_times = _show_times;
		open(fname);
	}

	FileLogger::~FileLogger(){

	}

	void FileLogger::open(const String &_fname){
		ofile.open(_fname, true);
	}

	static const char *__lsep1 = " [Thread=";
	static const char *__lsep2 = "]: ";

	void FileLogger::write(){
		ldata.lock();
		if(!ofile.opened()){
			ldata.unlock();
		}
		if(ldata[ThreadManager::getCurrentThreadID()].toString().size() > 0){
			//write((void *).c_str(), ldata.toString().size());
			ofile << ldata[ThreadManager::getCurrentThreadID()].toString() << xvr2::NL;
			ldata[ThreadManager::getCurrentThreadID()].clear();
		}
		ofile.flush();
		ldata.unlock();
	}

	void FileLogger::append(const xvr2::String &s){
		ldata.lock();
		if(ldata[ThreadManager::getCurrentThreadID()].toString().size() == 0){
			if(show_times){
				Timestamp t;
				ldata[ThreadManager::getCurrentThreadID()] << t.toString();
			}
			ldata[ThreadManager::getCurrentThreadID()] << " (" << ((UInt64)ThreadManager::getCurrentThread()) << "," << ((UInt64)ThreadManager::getCurrentBackgroundFunction()) << ") ";
			if(ThreadManager::currentIsMain()){
				ldata[ThreadManager::getCurrentThreadID()] << " [Main Thread]: ";
			}
			else{
				ldata[ThreadManager::getCurrentThreadID()] << __lsep1
						<< ThreadManager::getCurrentThreadID()
						<< __lsep2;
			}
		}
		ldata[ThreadManager::getCurrentThreadID()] << s;
		ldata.unlock();
	}

	//End implementation of class: FileLogger
}

