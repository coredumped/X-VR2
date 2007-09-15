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
#include<xvr2/Vector.h>
#include<xvr2/String.h>
#include<xvr2/Mutex.h>
#include<iostream>

template<typename _Tp>
void print_r(const std::vector<_Tp> &arr){
	std::cout << "[";
	for(_Tp i = 0; i < (_Tp)arr.size(); i++){
		if(i > 0){
			std::cout << ",";
		}
		std::cout << arr[i];
	}
	std::cout << "]" << std::endl;
}

int main(int argc, char *argv[]){
	xvr2::String h = "hello world";
	xvr2::Vector<int> a;
	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	std::vector<int> b;
	
	b = a;
	std::cout << "a: " << a.toString() << std::endl;
	std::cout << "b: ";
	print_r<int>(b);
	std::cout << h << std::endl;
	
	xvr2::Vector< xvr2::Vector<int> > c;
	c.push_back(a);
	c.push_back(a);
	std::cout << "c: " << c.toString() << std::endl;
	return 0;
}
