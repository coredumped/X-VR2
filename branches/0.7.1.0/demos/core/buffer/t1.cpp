/* $Id$ */

#include<xvr2/Buffer.h>
#include<xvr2/Console.h>
#include<iostream>

using xvr2::String;
using xvr2::Buffer;
using xvr2::NL;
using std::cout;
using std::endl;

xvr2::Console con;

int main(int argc, char *argv[]){
	Buffer buf3;
	String text = "cruel ";
	Buffer buf("Hello world", 12, true);
	con << (char *)buf.data() << NL;
	buf.insert(6, text);
	
	con << (char *)buf.data() << NL;
	
	Buffer buf2 = buf.cloneMe();
	con << (char *)buf2.data() << NL;
	
	//buf3 = buf.cloneMe();
	//con << (char *)buf3.data() << NL;
	//buf2 = 
	return 0;
}
