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
#include<xvr2/Pipeline.h>
#include<xvr2/String.h>
#include<xvr2/ThreadManager.h>
#include<iostream>
#include<fstream>

using xvr2::String;

class ChangeSpaces : public xvr2::PipelineFilter<xvr2::String> {
	public:
		ChangeSpaces(){ }
		xvr2::String operator()(const xvr2::String &in){
			xvr2::String oper = in;
			oper.replace(' ', "\\032");
			return xvr2::String(oper);
		}
};

class ToLowercase : public xvr2::PipelineFilter<xvr2::String> {
	public:
		ToLowercase(){ }
		xvr2::String operator()(const xvr2::String &in){
			xvr2::String oper = in;
			oper.toLowerCase();
			return xvr2::String(oper);
		}
};

int main(int argc, char *argv[]){
	//ChangeSpaces spacekiller;
	char spinner[] = { '/', '-', '\\', '|'};
	int si = 0;
	String val = "Hello World";
	if(argc > 1){
		for(int fi = 1; fi < argc; fi++){
			std::ifstream f(argv[fi]);
			while(!f.eof()){
				val.append(1, f.get());
			}
			f.close();
		}
	}
	xvr2::Pipeline<xvr2::String> p;
	p.addFilter(new ChangeSpaces());
	p.addFilter(new ToLowercase());
	//xvr2::ThreadManager::start(p);
	p.start();
	xvr2::Pipeline<xvr2::String>::Reader result = p.write(val);
	//std::cout << "Before: " << val << " ";
	std::cout.flush();
	while(!result.finished()){
		usleep(100);
		std::cout << spinner[(si++ % 4)] << "\b";
	}
	val = result.read();
	std::cout << "\nAfter: " << val << std::endl;
	p.shutdown();

	return 0;
}
