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
#include"Logger.h"

namespace xvr2 {

	Logger::Logger(){

	}

	Logger::~Logger(){

	}

	Logger &Logger::operator << (const String &s){
		if(s.equals(xvr2::NL)){
			write();
		}
		else{
			append(s);
		}
		return *this;
	}

	Logger &Logger::operator << (const StringBuffer &s){
		if(s.toString().compare(xvr2::NL) == 0){
			write();
		}
		else{
			append(s);
		}
		return *this;
	}

	Logger &Logger::operator << (Logger &l){
		std::string s = l.toString();
		append(s);
		return *this;
	}

	Logger &Logger::operator << (Object &s){
		if(s.toString().compare(xvr2::NL) == 0){
			write();
		}
		else{
			append(s);
		}
		return *this;
	}
}
