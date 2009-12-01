#include<xvr2.h>

using namespace xvr2;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]){
	if(argc <= 2){
		cerr << "Usage: " << argv[0] << " <ip address or hostname> <port>" << endl;
		return 1;
	}
	Net::UDPSocket client(argv[1], atoi(argv[2]));
	for(int i = 0; i < 25; i++){
		client.send<int>(&i);
	}
	return 0;
}
