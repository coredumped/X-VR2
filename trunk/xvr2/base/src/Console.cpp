/*
 * $Id$
 */
#include<xvr2/Console.h>
#include<xvr2/StandardError.h>
#include<xvr2/StandardOutput.h>
#include<xvr2/StandardInput.h>
#include<xvr2/Mutex.h>

namespace xvr2{
	
#ifdef USE_DEBUG
	Console __debug_console;
#endif

	/** Mutex for I/O ops under the Console class */
	static Mutex __conm;

	Console::Console(){
#ifndef USING_GCC3
		setClassName(xvr2::_xvr2Console);
#endif
		out = 0;
		err = 0;
		out = new StandardOutput();
		err = new StandardError();
		in  = new StandardInput();
		using_builtin_out = true;
		using_builtin_err = true;
		using_builtin_in  = true;
	}

	Console::~Console(){
		if(using_builtin_out && (out != 0))
				xvr2_delete(out);
		if(using_builtin_err && (err != 0))
				xvr2_delete(err);
		if(using_builtin_in && (in != 0))
				xvr2_delete(in);
	}

	void Console::setOutput(TextOutput *to){
		if(to == 0){
			if(!using_builtin_out){
				out = new StandardOutput();
				using_builtin_out = true;
			}
		}
		else{
			if(using_builtin_out){
				if(out != 0){
					xvr2_delete(out);
				}
				using_builtin_out = false;
			}
			out = to;
		}
	}

	void Console::setInput(TextInput *ti){
		if(ti == 0){
			if(!using_builtin_in){
				in = new StandardInput();
				using_builtin_in = true;
			}
		}
		else{
			if(using_builtin_in){
				if(in != 0){
					xvr2_delete(in);
				}
				using_builtin_in = false;
			}
			in = ti;
		}
	}

	void Console::setErrorOutput(TextOutput *te){
		if(te == 0){
			if(!using_builtin_err){
				err = new StandardOutput();
				using_builtin_err = true;
			}
		}
		else{
			if(using_builtin_err){
				if(err != 0){
					xvr2_delete(err);
				}
				using_builtin_err = false;
			}
			err = te;
		}
	}

	void Console::outWrite(const void *buf, UInt32 siz){
		if(out != 0){
			__conm.lock();
			try{
				out->write(buf, siz);
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::outWrite(const String &text){
		if(out != 0){
			__conm.lock();
			try{
				out->write(text.toCharPtr(), text.size());
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::outWriteLine(const void *buf, UInt32 siz){
		if(out != 0){
			__conm.lock();
			try{
				out->writeLine(buf, siz);
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::outWriteLine(const String& text){
		if(out != 0){
			__conm.lock();
			try{
				out->writeLine(text.toCharPtr(), text.size());
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}



	void Console::errWrite(const void *buf, UInt32 siz){
		if(err != 0){
			__conm.lock();
			try{
				err->write(buf, siz);
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::errWrite(const String& text){
		if(err != 0){
			__conm.lock();
			try{
				err->write(text.toCharPtr(), text.size());
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::errWriteLine(const void *buf, UInt32 siz){
		if(err != 0){
			__conm.lock();
			try{
				err->writeLine(buf, siz);
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::errWriteLine(const String& text){
		String *t;
		t = (String *)&text;
		if(err != 0){
			__conm.lock();
			try{
				err->writeLine(text.toCharPtr(), t->size());
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::read(void *buf, UInt32 size){
		if(in != 0){
			__conm.lock();
			try{
				in->read(buf, size);
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}

	void Console::readLine(String &line){
		if(in != 0){
			__conm.lock();
			try{
				in->readLine(line);
			}
			catch(...){
				__conm.unlock();
				throw;
			}
			__conm.unlock();
		}
		else throw Exception::NullPointer();
	}
};

