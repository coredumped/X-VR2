#include<xvr2/Array.h>
#include<xvr2/Console.h>

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
		tmp_s = i;
		b.add(tmp_s);
		//con << tmp_s << "\n";
	}
	for(i = 0; i < b.size(); i++){
		con << "a[" << i << "] = " << a[i] << "\t";
		con << "b[" << i << "] = " << b[i] << "\n";
	}
	return 0;
}
