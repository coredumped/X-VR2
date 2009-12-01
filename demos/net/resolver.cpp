#include<xvr2/IPv4Resolver.h>
#include<xvr2/String.h>

using namespace xvr2;
using namespace xvr2::Net;

int main(int argc, char *argv[]){
	IPv4Address *addr;
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			std::cout << argv[i] << " is at ";
			try{
				addr = IPv4Resolver::resolve(argv[i]);
				std::cout << addr->toString() << std::endl;
				delete addr;
			}
			catch(Exception e1){
				std::cout << e1.toString() << std::endl;
			}
		}
	}
	else{
		addr = IPv4Resolver::resolve("www.google.com");
		std::cout << "www.google.com is at ";
		std::cout << addr->toString() << std::endl;
		delete addr;
	}
	return 0;
}
