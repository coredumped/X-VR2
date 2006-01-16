#include<xvr2.h>

using namespace xvr2;

Console con;

int main(){
	int i;
	Util::List<int> a;
	Util::List<String> b;
	String tmp_s;
	//Load an array of ints
	for(i = 0; i < 35; i++){
		a.add(i);
		tmp_s = i;
		b.add(tmp_s);
	}
	for(i = 0; i < b.size(); i++){
		con << "a[" << i << "] = " << a.get(i) << "\t";
		con << "b[" << i << "] = " << b.get(i) << "\n";
	}

	return 0;
}

