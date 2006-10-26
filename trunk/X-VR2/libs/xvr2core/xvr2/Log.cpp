/*
 * This class manages basic log file handling
 *
 * $Id$
 */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
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

	Log::Log(const String &fname, bool _show_times):StdioOutputFile(fname){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Log);
#endif
		show_times = _show_times;
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
			write((void *)ldata.toString().toCharPtr(), ldata.toString().size());
		}
		StdioOutputFile::flush();
	}

	//End implementation of class: Log
};

