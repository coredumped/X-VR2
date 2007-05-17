#include<xvr2/UDPServerSocket.h>

using namespace xvr2;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]){
	int data;
	if(argc <= 1){
		cerr << "Usage: " << argv[0] << " <port>" << endl;
		return 1;
	}
	Net::UDPServerSocket server(atoi(argv[1]));
	cout << "Receive timeout set to 15 seconds" << endl;
	server.setRecvTimeout(15000);
	while(true){
		try{
			server.receive<int>(&data);
		}
		catch(...){
			break;
		}
		cout << data << endl;
	}
	return 0;
}
