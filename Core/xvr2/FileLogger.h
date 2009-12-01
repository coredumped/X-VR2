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
#ifndef __XVR2_FILE_LOGGER_H__
#define __XVR2_FILE_LOGGER_H__

#include<xvr2/CoreExceptions.h>
#include<xvr2/StdioOutputFile.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/Map.h>
#include<xvr2/Logger.h>

namespace xvr2{
	/** This class manages basic log file handling */
	class FileLogger:public Logger {
		private:
			StdioOutputFile ofile;
			/** Log line internal data */
			Map<UInt32, StringBuffer> ldata;
		protected:
			/** Whether to show a timestamp or not in every log line. */
			bool show_times;
			void write();
			void append(const xvr2::String &s);
		public:
			FileLogger(bool _show_times = true);
			void open(const String &_fname);
			/** Builds a log object which will dump log lines
			 *  in the file specified by fname and printing
			 *  timestamps on each line if _show_times is true */
			FileLogger(const String &fname, bool _show_times = true);
			virtual ~FileLogger();
			// /** Send string s to the log buffer */
			// FileLogger &operator << (const String &s);
			// /** Flushes the log line to the log file, this method
			//  *  will be automatically called whenever the xvr2::NL
			//  *  is appended to the log stream */
			// void flush();
			// virtual void close();
	};
}

#endif

