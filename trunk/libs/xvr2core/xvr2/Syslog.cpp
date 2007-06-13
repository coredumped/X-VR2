/*
 * This class handles the Syslog daemon
 *
 * $Id$
 */
#include"config.h"
#include "Syslog.h"
#include<syslog.h>

namespace xvr2{

	// Start definition of local variables
	// End definition of local variables

	// Start definition of local functions
	// End definition of local functions




	//Start implementation of class: Syslog

	Syslog::Syslog(){
	}

	Syslog::~Syslog(){
	}

	void Syslog::Log(const char *logmsg, int type){
		if(type == -666){
			//Do an INFO log on facility LOG_USER
			syslog(LOG_USER|LOG_INFO, "%s", logmsg);
		}
		else{
			//Do a proper log as specified in type
			syslog(type, "%s", logmsg);
		}
	}

	void Syslog::Log(const String &logmsg1, int type){
		if(type == -666){
			//Do an INFO log on facility LOG_USER
			syslog(LOG_USER|LOG_INFO, "%s", logmsg1.toCharPtr());
		}
		else{
			//Do a proper log as specified in type
			syslog(type, "%s", logmsg1.toCharPtr());
		}
	}

	//void Syslog::(){
	//}
	//void Syslog::(){
	//}

	//End implementation of class: Syslog
};
