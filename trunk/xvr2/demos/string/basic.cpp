#include<xvr2.h>

using namespace xvr2;
using namespace std;

String *f1(const String &s1, const String &s2){
	String *r;
	r = new String(s1);
	r->concat(s2);
	return r;
}

int main(){
	String s1, s2, *r, pi;
	s1.assign("hola");
	s2 = "mundo";
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	s1.concat(' ');
	cout << "s1 . ' ' = \"" << s1 << "\"" << endl;
	r = f1(s1, s2);
	cout << "f1(s1, s2): " << r->toCharPtr() << endl;
	pi = 3;
	cout << "pi: " << pi << endl;
	pi += ".141592654 ";
	cout << "pi . '.141592654 ' = \"" << pi << "\"" << endl;
	if(pi.startsWith(3.14)){
		cout << "pi starts with 3.14" << endl;
	}
	else{
		cout << "pi DOES NOT starts with 3.14" << endl;
	}
	cout << "pi.trimRight(): \"" << pi.trimRight() << "\"" << endl;
	cout << "pi: \"" << pi << "\"" << endl;
	r->toUpperCase();
	cout << "Uppercase r: \"" << r->toCharPtr() << "\"" << endl;
	delete r;
	return 0;
}
