#include<xvr2.h>
using namespace xvr2;
using std::cout;
using std::endl;

int main(int argc, char *argv[]){
	//Tokenizer *tok;
	String str;
	if(argc < 3){
		return 1;
	}
	Tokenizer tok(argv[1], argv[2]);
	while(!tok.finished()){
		cout << tok.next() << endl;
	};
	return 0;
}
