/*
 * $Id$
 */
#include"xvr2/Object.h"
#include"xvr2/TextOutput.h"
#include"xvr2/Console.h"
#include"xvr2/DebugConsole.h"

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
