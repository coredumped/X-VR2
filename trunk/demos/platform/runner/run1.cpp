#include<xvr2/String.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/ProcessRunner.h>
#include<xvr2/Buffer.h>
#include<iostream>

using namespace xvr2;

int main(int argc, char *argv[]){
	Buffer buf;
	StringBuffer cmd;
	for(int i = 1; i < argc; i++){
		cmd << argv[i] << " ";
	}
	Platform::ProcessRunner::execute(cmd.toString(), buf);

	std::cout << (const char *)buf.data();
	std::cout.flush();
	return 0;
}
