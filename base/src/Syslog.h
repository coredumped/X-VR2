/*
 * $Id$
 */
#ifndef __XVR2_Syslog_H__
#define __XVR2_Syslog_H__

#include<Unix.h>

namespace xvr2{
	/**
	 * This class handles the Syslog daemon
	 *
	 * At the moment this class is very system dependent
	 * for the <b>log types</b> accepted, right now we are using 
	 * the current C library implementation in your 
	 * platform, under glibc it is an ORed combination of
	 * facility and level, the facility can be any one of:
	 *
	 * <b>LOG_AUTH</b>
	 *        security/authorization  messages  (DEPRECATED  Use
	 *        <b>LOG_AUTHPRIV</b> instead)<br>
	 * <b>LOG_AUTHPRIV</b>
	 *        security/authorization messages (private)<br>
	 * <b>LOG_CRON</b>
	 *        clock daemon (cron and at)<br>
	 * <b>LOG_DAEMON</b>
	 *        system daemons without separate facility value<br>
	 * <b>LOG_FTP</b>
	 *        ftp daemon<br>
	 * <b>LOG_KERN</b>
	 *        kernel messages<br>
	 * <b>LOG_LOCAL0</b> through <b>LOG_LOCAL7</b>
	 *        reserved for local use<br>
	 * <b>LOG_LPR</b>
	 *        line printer subsystem<br>
	 * <b>LOG_MAIL</b>
	 *        mail subsystem<br>
	 * <b>LOG_NEWS</b>
	 *        USENET news subsystem<br>
	 * <b>LOG_SYSLOG</b>
	 *        messages generated internally by syslogd<br>
	 * <b>LOG_USER</b> (default)
	 *        generic user-level messages<br>
	 * <b>LOG_UUCP</b>
	 *        UUCP Subsystem<br>
	 * <br>These are the values for the level:<br>
	 * <b>LOG_EMERG</b>
	 *        system is unusable<br>
	 * <b>LOG_ALERT</b>
	 *        action must be taken immediately<br>
	 * <b>LOG_CRIT</b>
	 *        critical conditions<br>
	 * <b>LOG_ERR</b>
	 *        error conditions<br>
	 * <b>LOG_WARNING</b>
	 *        warning conditions<br>
	 * <b>LOG_NOTICE</b>
	 *        normal, but significant, condition<br>
	 * <b>LOG_INFO</b>
	 *        informational message<br>
	 * <b>LOG_DEBUG</b>
	 *        debug-level message<br>
	 * <p><b>IN GLIBC THE ABOVE VALUES ARE DEFINED IN syslog.h</b><br>
	 *
	 * <p><b>TODO:</b><br>
	 *  Add portability for BSD based unices<br>
	 *  verify that the glibc function <b>syslog</b> is reentrant<br>
	 */
	class Syslog:public Unix{
		private:
		protected:
		public:
			/** Default constructor */
			Syslog();
			~Syslog();
			/** This will append a new log message to the syslog
			 *  daemon queue if you use the default logtype value it 
			 *  will use the facility LOG_USER and the priority 
			 * LOG_INFO
			 */
			static void Log(const char *logmsg, int logtype=-666);
			/** This will append a new log message to the syslog
			 *  daemon queue if you use the default logtype value it 
			 *  will use the facility LOG_USER and the priority 
			 * LOG_INFO
			 */
			static void Log(const String &logmsg, int logtype=-666);
	};
};

#endif
