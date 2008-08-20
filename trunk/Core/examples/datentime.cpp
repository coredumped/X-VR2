/*
 * $Id$
 *
 * X-VR2
 *
 * Copyright (C) Juan V. Guerrero 2008
 *
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#include<xvr2/Date.h>
#include<xvr2/Timestamp.h>
#include<xvr2/String.h>
#include<iostream>

int main(){
	xvr2::Date now;
	std::cout << "Current date:              " << now << " (unixtime: " << now.unixTime() << ")" << std::endl;
	std::cout << "Current date + 60 seconds: " << (now + 60) << std::endl;
	std::cout << "Current date - 30 seconds: " << (now - 30) << std::endl;
	std::cout << "15 seconds + current date: " << (15 + now) << std::endl;
	xvr2::Timestamp t;
	std::cout << "Timestamp + 60 seconds:    " << (t + 60) << std::endl;
	return 0;
}
