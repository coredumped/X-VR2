#include<xvr2/Regex.h>
#include<iostream>


int main(){
	using namespace xvr2;
	Util::Regex *r;
	r = new Util::Regex();
	r->pattern("666");
	if(r->matches("call it 666 the number of the beast"))
		std::cout << "Pattern match works fine" << std::endl;
	else
		std::cout << "Pattern match fails" << std::endl;
	xvr2_delete(r);
	return 0;
}
