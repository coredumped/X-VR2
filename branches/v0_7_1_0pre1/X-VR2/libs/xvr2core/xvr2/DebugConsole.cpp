/*
 * $Id$
 */
#include"config.h"
#include"Object.h"
#include"TextOutput.h"
#include"Console.h"
#include"DebugConsole.h"

namespace xvr2 {
	
	DebugConsole debugConsole;

	DebugConsole::DebugConsole():Console(){
	}
	void DebugConsole::setOutput(TextOutput *to){
		setErrorOutput(to);
	}
	const DebugConsole &DebugConsole::operator<<(const String &s) const {
		errWrite(s);
		return *this;
	}
};