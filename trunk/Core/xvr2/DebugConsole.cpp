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
	bool DebugConsole::enabled(){
		return _enabled;
	}
	void DebugConsole::enable(){
		_enabled = true;
	}
	void DebugConsole::disable(){
		_enabled = false;
	}
}
