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
		cerr << "You must at least specify the destination port like this:\n\t" << argv[0] << " <port>" << endl;
		return 1;
	}
	IPv4Address addr("127.0.0.1");
	::message msg(1, 2, 3);
	UDP::send(addr, atoi(argv[1]), &msg, sizeof(message));
	return 0;
}
