/* $Id$ */

#include<xvr2/File.h>
#include<xvr2/String.h>
#include<xvr2/Buffer.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/Console.h>
#include<iostream>

using xvr2::String;
using xvr2::Buffer;
using xvr2::StringBuffer;
using xvr2::File;
using xvr2::NL;
using std::cout;
using std::endl;

xvr2::Console con;

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		StringBuffer out_f;
		con << "Reading: " << argv[i] << "... ";
		File f(argv[i], xvr2::READ_ONLY);
		Buffer b;
		f.readAll(b);
		out_f << i << ".copy";
		File out(out_f.toString(), xvr2::WRITE_ONLY);
		out.write("A copy of: ");
		out.write(argv[i]);
		out.write(NL);
		out.write(b);
		con << (const char *)b.data() << NL;
		out.close();
		f.close();
		con << "done" << NL;
	} 
	return 0;
}
