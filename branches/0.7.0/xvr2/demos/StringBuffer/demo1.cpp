#include<xvr2.h>

using namespace xvr2;
int main(){
	Console con;
	StringBuffer buffer;
	StringBuffer buffer2("bye bye\n");
	buffer << "Hello" << " World\n" << "This is a " << "beautiful day\n";
	con << buffer.toString();
	con << buffer2.toString();
	return 0;
}
