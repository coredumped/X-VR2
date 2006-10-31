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
#include<xvr2/CoreExceptions.h>
#include<xvr2/PlatformException.h>
#include<xvr2/DebugConsole.h>
#include"ProcessRunner.h"
#include<cerrno>
#include<cstdio>
#include<cstdlib>
#include<deque>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

namespace xvr2 {
	namespace Platform {

		static std::deque<int> __closable_fds;

		int ProcessRunner::execute(const String &command){
			int retcode;
			retcode = system(command.toCharPtr());	
			if(retcode == -1){
				throw SystemException(errno);
			}
#ifdef XVR2_HOST_PLATFORM_LINUX
			return WEXITSTATUS(retcode);
#else
			return retcode;
#endif
		}

		int ProcessRunner::execute(const String &command, Buffer &_output){
			int retcode;
			FILE *fptr;
			char buf[512];
			fptr = popen(command.toCharPtr(), "r");
			while(fgets(buf, 512, fptr)){
				_output << buf;
			}
			retcode = pclose(fptr);
			return retcode;
		}

/////////////////////// CONSTRUCTORS ////////////////////////////////////
		struct _opaque {
			String cmd;
			int retcode;
			pid_t pid;
			_opaque(){
				pid = -1;
				retcode = -1;
			}
		};

		ProcessRunner::ProcessRunner(){
			_opaque *o = new _opaque();
			stack = o;
		}

		ProcessRunner::ProcessRunner(const String &_cmdline){
			_opaque *o = new _opaque();
			stack = o;
			o->cmd = _cmdline;
		}

//////////////////////// DESTRUCTORS ////////////////////////////////////
		ProcessRunner::~ProcessRunner(){
			_opaque *o = (_opaque *)stack;
			delete o;
		}

//////////////////////// METHOD DEFINITIONS /////////////////////////////
		RawInputStream &ProcessRunner::errorStream(){
			return err;
		}

		RawInputStream &ProcessRunner::outputStream(){
			return out;
		}

		RawOutputStream &ProcessRunner::inputStream(){
			return in;
		}

		void ProcessRunner::kill(int signal){
			_opaque *o = (_opaque *)stack;
			if(::kill(o->pid, signal) == -1){
				throw SystemException(errno);
			}
		}

		Int32 ProcessRunner::pid(){
			_opaque *o = (_opaque *)stack;
			return o->pid;
		}

		int ProcessRunner::exitCode(){
			_opaque *o = (_opaque *)stack;
			return o->retcode;
		}

////////////////////// THE NEAT STUFF STARTS HERE, FINALLY!!!!! //////////////////////

		void ProcessRunner::start(){
			_opaque *o = (_opaque *)stack;
			start(o->cmd);
		}

		static const char *__cmt1 = "Unable to create standard input pipeline.";
		static const char *__cmt2 = "Unable to create standard output pipeline.";
		static const char *__cmt3 = "Unable to create standard error pipeline.";

		static const int __FD_STDIN  = 0;
		static const int __FD_STDOUT = 1;
		static const int __FD_STDERR = 2;

		void ProcessRunner::start(const String &cmdline){
			_opaque *o = (_opaque *)stack;
			o->cmd = cmdline;
			//Create the pipes
			int in_fds[2];
			int out_fds[2];
			int err_fds[2];
#ifdef USE_DEBUG
			debugConsole << "Creating stdin pipe..." << NL;
#endif
			if(pipe(in_fds) < 0){
				throw ProcessException(errno, __cmt1);
			}
#ifdef USE_DEBUG
			debugConsole << "Creating stdout pipe..." << NL;
#endif
			if(pipe(out_fds) < 0){
				throw ProcessException(errno, __cmt2);
			}
#ifdef USE_DEBUG
			debugConsole << "Creating stderr pipe..." << NL;
#endif
			if(pipe(err_fds) < 0){
				throw ProcessException(errno, __cmt3);
			}
#ifdef USE_DEBUG
			debugConsole << "forking..." << NL;
#endif
			o->pid = fork();
			if(o->pid == 0){
				//Child process
				//Connecting pipelines
				dup2(in_fds[0],  __FD_STDIN);
				dup2(out_fds[1], __FD_STDOUT);
				dup2(err_fds[1], __FD_STDERR);
				//Close the parent's pipeline ends
				if(in_fds[1]  != __FD_STDIN)  ::close(in_fds[1]);
				if(out_fds[0] != __FD_STDOUT) ::close(out_fds[0]);
				if(err_fds[0] != __FD_STDERR) ::close(err_fds[0]);
				//Close fds not in use
				while(__closable_fds.size() > 0){
					::close(__closable_fds.at(0));
					__closable_fds.pop_front();
				}
				//Start the process per se.
				execl("/bin/sh", "sh", "-c", o->cmd.toCharPtr(), (char *)0);
				_exit(127);
			}
			//////////////////// PARENT PROCESS ///////////////
			else if(o->pid == -1){
				//Close the pipelines
				::close(in_fds[1]);
				::close(in_fds[0]);
				::close(out_fds[1]);
				::close(out_fds[0]);
				::close(err_fds[1]);
				::close(err_fds[0]);
				throw ProcessException(errno);
			}
			else{
				//Open X-VR2 Streams
#ifdef USE_DEBUG
				debugConsole << "Attaching stdin, stdout and stderr to in, out, err respectively" << NL;
#endif
				in.open(in_fds[1]);
				out.open(out_fds[0]);
				err.open(err_fds[0]);
			}
		}

		int ProcessRunner::wait(){
			_opaque *o = (_opaque *)stack;
			int retcode;
			__closable_fds.push_back(in.fd());
			__closable_fds.push_back(out.fd());
			__closable_fds.push_back(err.fd());
#ifdef USE_DEBUG
			debugConsole << "Waiting for process: " << o->pid << " to finish..." << NL;
#endif
			if(waitpid(o->pid, &retcode, 0) == -1){
				throw ProcessException(errno, "Weird problem on ProcessRunner::wait()");
			}
			if(WIFEXITED(retcode)){
				o->retcode = WEXITSTATUS(retcode);
			}
			return o->retcode;
		}




/////////////////////// SPECIFIC PROCESS EXCEPTIONS //////////////////////////////////

		ProcessException::ProcessException(int c):SystemException(c){}

		ProcessException::ProcessException(int c, const String &msg):SystemException(c){
			_comment = msg;
		}

		const String &ProcessException::comment(){
			return _comment;
		}

	};
};

