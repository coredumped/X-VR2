#include<xvr2.h>

using namespace xvr2;
using namespace xvr2::Net;

int main(int argc, char *argv[]){
	IPv4Address *addr;
	String *ip;
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			addr = IPv4Resolver::resolve(argv[i]);
			ip = addr->toString();
			std::cout << argv[i] << " is at ";
			std::cout << ip->toCharPtr() << std::endl;
			delete addr;
			delete ip;
		}
	}
	else{
		addr = IPv4Resolver::resolve("www.google.com");
		ip = addr->toString();
		std::cout << "www.google.com is at ";
		std::cout << ip->toCharPtr() << std::endl;
		delete addr;
		delete ip;
	}
	return 0;
}