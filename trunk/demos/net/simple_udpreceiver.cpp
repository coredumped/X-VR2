/*
 * $Id$
 */
#include<xvr2/UDP.h>
#include<iostream>

using namespace xvr2;
using namespace xvr2::Net;
using std::cout;
using std::cerr;
using std::endl;

class message {
	public:
		int a;
		int b;
		int c;
		message(){;}
		message(int _a, int _b, int _c){
			a = _a;
			b = _b;
			c = _c;
		}
};

int main(int argc, char *argv[]){
	if(argc <= 1){
		cerr << "You must at least specify the listening port like this:\n\t" << argv[0] << " <port>" << endl;
		return 1;
	}
	message msg;
	UDP::receive(atoi(argv[1]), (void *)&msg, sizeof(message), 0, 300000);
	cout << "a: " << msg.a << endl;
	cout << "b: " << msg.b << endl;
	cout << "c: " << msg.c << endl;
	return 0;
}
