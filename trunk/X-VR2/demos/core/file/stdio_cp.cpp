// $LastChangedDate$
// $LastChangedRevision$
// $LastChangedBy$
#include<xvr2/StdioInputFile.h>
#include<xvr2/StdioOutputFile.h>
#include<xvr2/StringBuffer.h>
#include<iostream>

#ifndef MAX_FILE_SIZE
#define MAX_FILE_SIZE 4194304L
#endif

#ifndef CHUNK_SIZE
#define CHUNK_SIZE (UInt32)MAX_FILE_SIZE
#endif

using xvr2::StdioInputFile;
using xvr2::StdioOutputFile;
using std::cout;
using std::endl; 

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		UInt32 s = 0;
		xvr2::StringBuffer newname;
		newname << i << ".copy";
		StdioInputFile in(argv[i]);
		StdioOutputFile out(newname.toString());
		xvr2::Buffer data;
		cout << argv[i] << " -> " << newname.toString() << "...";
		cout.flush();
		if(in.size() < MAX_FILE_SIZE){
			in.readAll(data);
			out << data;
			s = in.size();
		}
		else{
			//File is too big, mmm, lets read it per chunks
			s = 0;
			while(!in.eof()){
				in.read(data, CHUNK_SIZE);
				out << data;
				s += data.size();
			}
		}
		out.flush();
		if(s == in.size()){
			cout << "success" << endl;
		}  
		else{
			cout << "failed (" << s << " != " << in.size() << ")" << endl;
		}
	}
	return 0;
}