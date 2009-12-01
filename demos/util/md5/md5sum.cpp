/* $Id$ */
#include<xvr2/String.h>
#include<xvr2/MD5.h>
#include<xvr2/StdioInputFile.h>
#include<iostream>

using xvr2::Util::MD5;
using xvr2::StdioInputFile;
using xvr2::Buffer;

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		MD5 a;
		StdioInputFile f(argv[i]);
		Buffer b;
		while(!f.eof()){
			f.read(b, 1024);
			a << b;
		}
		std::cout << a.digest() << "  " << argv[i] << std::endl;
	}
}
