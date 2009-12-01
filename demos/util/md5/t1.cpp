/* $Id$ */
#include<xvr2/String.h>
#include<xvr2/MD5.h>
#include<iostream>

using xvr2::Util::MD5;

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		MD5 a(argv[i]);
		std::cout << a.digest() << " - " << argv[i] << std::endl;
	}
}
