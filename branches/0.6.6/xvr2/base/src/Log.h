/*
 * $Id$
 */
#ifndef __XVR2_Log_H__
#define __XVR2_Log_H__

#include<System.h>
#include<BaseFile.h>
#include<Mutex.h>

namespace xvr2{
	/**
	 * This class manages basic log file handling
	 *
	 * STATUS: IN PROGRESS
	 *
	 */
	class Log:public System{
		private:
			Mutex mutex;
			BaseFile *f;
		protected:
			void open();
			void close();
		public:
			Log(const String &fname);
			~Log();
			void log(const char *s);
			void log(const String &s);
			void logf(const char *fmt, ...);
			void logf(const String &s, ...);
			
	};
};

#endif