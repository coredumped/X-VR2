/* $Id$ */
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

#ifndef __XVR2_PLATFORM_PROCESS_RUNNER_H__
#define __XVR2_PLATFORM_PROCESS_RUNNER_H__

#include<xvr2/SystemException.h>
#include<xvr2/Platform/PlatformException.h>
#include<xvr2/RawInputStream.h>
#include<xvr2/RawOutputStream.h>
#include<xvr2/String.h>
#include<xvr2/Buffer.h>

namespace xvr2 {
	namespace Platform {

		/** Generalized process execution class, it may work just like when you
		 *  call the c library's system() function or even better, I may let
		 *  you manipulate interactive commands as well. */
		class ProcessRunner:public Object {
			protected:
				RawInputStream err;
				RawInputStream out;
				RawOutputStream in;
				void *stack;
			public:
				ProcessRunner();
				ProcessRunner(const String &_cmdline);
				~ProcessRunner();
				void start();
				void start(const String &cmdline);
				RawInputStream &errorStream();
				RawInputStream &outputStream();
				RawOutputStream &inputStream();
				/** Returns the exit code for the running process or an exception
				 *  if it has not finished running */
				int exitCode();
				/** Returns the process numeric ID as assigned by the OS */
				Int32 pid();
				void kill(int signal);
				int wait();
				bool isRunning();
				
				static int execute(const String &command);
				static int execute(const String &command, Buffer &_output);
		};

		class ProcessException : public SystemException {
			protected:
				String _comment;
			public:
				ProcessException(int c);
				ProcessException(int c, const String &msg);
				const String &comment();
		};
	};
};

#endif
