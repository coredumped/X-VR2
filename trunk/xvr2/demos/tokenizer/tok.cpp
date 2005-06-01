#include<xvr2.h>
using namespace xvr2;
using namespace std;

int main(int argc, char *argv[]){
	Tokenizer *tok;
	if(argc <= 1 || argc > 3){
		return 1;
	}
	tok = new Tokenizer(argv[1], argv[2]);
	while(true){
		try{
			cout << tok->next(true) << endl;
		}
		catch(...){
			break;
		}
	}
	return 0;
}
