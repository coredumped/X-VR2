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
#include"Log.h"
#include<xvr2/Timestamp.h>
#include<xvr2/ThreadManager.h>

namespace xvr2{

	// Start definition of local variables
	// End definition of local variables

	// Start definition of local functions
	// End definition of local functions




	//Start implementation of class: Log
	Log::Log(bool _show_times){
		show_times = _show_times;
	}

	Log::Log(const String &fname, bool _show_times):StdioOutputFile(fname, true){
		show_times = _show_times;
	}

	Log::~Log(){
	}

	void Log::open(const String &_fname){
		StdioOutputFile::open(_fname, true);
	}

	void Log::close(){
		StdioOutputFile::close();
	}

	static const char *__lsep1 = " [Thread=";
	static const char *__lsep2 = "]: ";

	Log &Log::operator << (const String &s){
		ldata << s;
		if(s.equals(NL)){
			String line = ldata.toString();
			ldata.clear();
			if(show_times){
				Timestamp t;
				ldata << t.toString();
			}
			ldata << __lsep1 << ThreadManager::getCurrentThreadID() << __lsep2 << line;
			Log::flush();
			ldata.clear();
		}
		return *this;
	}

	void Log::flush(){
		if(ldata.toString().size() > 0){
			write((void *)ldata.toString().c_str(), ldata.toString().size());
		}
		StdioOutputFile::flush();
	}

	//End implementation of class: Log
}

