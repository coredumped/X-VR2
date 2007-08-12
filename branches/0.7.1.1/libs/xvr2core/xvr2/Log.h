/*
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
#ifndef __XVR2_Log_H__
#define __XVR2_Log_H__

#include<xvr2/CoreExceptions.h>
#include<xvr2/StdioOutputFile.h>
#include<xvr2/StringBuffer.h>

namespace xvr2{
	/** This class manages basic log file handling */
	class Log:public StdioOutputFile {
		private:
			/** Log line internal data */
			StringBuffer ldata;
		protected:
			/** Wheter to show a timestamp or not in every log line. */
			bool show_times;
		public:
			Log(bool _show_times = true);
			void open(const String &_fname);
			/** Builds a log object which will dump log lines
			 *  in the file specified by fname and printing
			 *  timestamps on each line if _show_times is true */
			Log(const String &fname, bool _show_times = true);
			virtual ~Log();
			/** Send string s to the log buffer */
			Log &operator << (const String &s);
			/** Flushes the log line to the log file, this method
			 *  will be automatically called whenever the xvr2::NL
			 *  is appended to the log stream */
			void flush();
			virtual void close();
	};
};

#endif
