// $LastChangedDate$
// $LastChangedRevision$
// $LastChangedBy$
#include<xvr2/StdioInputFile.h>
#include<iostream>

#ifndef MAX_FILE_SIZE
#define MAX_FILE_SIZE 4194304L
#endif

#ifndef CHUNK_SIZE
#define CHUNK_SIZE (UInt32)MAX_FILE_SIZE
#endif

using xvr2::StdioInputFile;
using std::cout;
using std::endl; 

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		StdioInputFile in(argv[i]);
		UInt32 s = 0;
		cout << argv[i] << " size: " << in.size() << endl;
		xvr2::Buffer data;
		if(in.size() < MAX_FILE_SIZE){
			cout << "Loading file contents to memory... ";
			cout.flush();
			in.readAll(data);
			s = data.size();
		}
		else{
			cout << "Performing chunk reading (using " << CHUNK_SIZE << "b sized chunks)...";
			cout.flush();
			while(!in.eof()){
				in.read(data, CHUNK_SIZE);
				s += data.size();
			}
		}
		if(s == in.size()){
			cout << "success" << endl;
		}  
		else{
			cout << "failed (" << s << " != " << in.size() << ")" << endl;
		}
	} 
	return 0;
}
