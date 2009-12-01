#include<xvr2/String.h>
#include<iostream>

using std::cout;
using std::cerr;
using std::endl;

using xvr2::String;

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		String p = argv[i];
		cout << argv[i] << " ";
		cout.flush();
		cout << p.toInt() << " " << p.toDouble() << " " << p.toInt64() << endl;
	}
	return 0;
}
