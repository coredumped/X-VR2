/*
 * This class manages basic log file handling
 *
 * $Id$
 */
#include<xvr2/Log.h>
#include<string>

namespace xvr2{

	// Start definition of local variables
	// End definition of local variables

	// Start definition of local functions
	// End definition of local functions




	//Start implementation of class: Log

	Log::Log(const String &fname){
#if __GNUC__ < 3
		setClassName(xvr2::_xvr2Log);
#endif
		f = new BaseFile(fname);
	}

	Log::~Log(){
		xvr2_delete(f);
	}

	void Log::log(const char *s){
		f->open(BaseFile::APPEND);
		f->write(s, strlen(s));
		f->close();
	}

	void Log::log(const String &s){
		f->open(BaseFile::APPEND);
		//f->write(s->toCharPtr(), s.size());
		f->close();
	}

	void Log::logf(const char *fmt, ...){
	}

	//void Log::(){
	//}

	//End implementation of class: Log
};
