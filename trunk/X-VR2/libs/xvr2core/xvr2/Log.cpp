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

	static const char *__lsep = ": ";

	Log &Log::write(void *data, UInt32 size){
		if(NL.equals((char *)data)){
			StdioOutputFile::write((void *)NL.toCharPtr(), NL.size());
			flush();
			return *this;
		}
		if(show_times){
			Timestamp t;
			std::string s = t.toString();
			StdioOutputFile::write((void *)s.c_str(), s.size());
			StdioOutputFile::write((void *)__lsep, 2);
		}
		StdioOutputFile::write((void *)data, size);
		return *this;
	}


	//End implementation of class: Log
};

