#include<xvr2.h>

using namespace xvr2;

Console con;

int main(){
	int i;
	Util::Array<int> a;
	Util::Array<String> b;
	String tmp_s;
	//Load an array of ints
	for(i = 0; i < 35; i++){
		a.add(i);
		/*tmp_s = i;
		con << tmp_s << "\n";*/
	}
	for(i = 0; i < 35; i++){
		con << "a[" << i << "] = " << i << "\n";
	}
	return 0;
}
