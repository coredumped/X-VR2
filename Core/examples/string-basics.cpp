#include<xvr2/String.h>
#include<iostream>
#include<xvr2/Mutex.h>

using xvr2::String;
using std::cout;
using std::cerr;
using std::endl;

String f1(const String &s1, const String &s2){
	String r = s1;
	r.concat(s2);
	return String(r);
}

void comparisons();

int main(){
	String s1, s2, pi;
	float nx = 3.14;
	s1.assign("hola");
	s2 = "mundo";
	cout << "==== Basic Stuff ====" << endl;
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	s1.concat(' ');
	cout << "s1 . ' ' = \"" << s1 << "\"" << endl;
	String r = f1(s1, s2);
	cout << "f1(s1, s2): " << r << endl;
	cout << "nx: " << nx << endl;
	pi = 3;
	cout << "pi: " << pi << endl;
	pi += ".141592654 ";
	cout << "pi += '.141592654 ' = \"" << pi << "\"" << endl;
	if(pi.startsWith(nx)){
		cout << "pi starts with " << nx << endl;
	}
	else{
		cout << "pi DOES NOT starts with " << nx << endl;
	}
	cout << "pi.trimRight(): \"" << pi.trimRight() << "\"" << endl;
	cout << "pi: \"" << pi << "\"" << endl;
	r.toUpperCase();
	cout << "Uppercase r: \"" << r << "\"" << endl;
	r.biteLeft(5);
	cout << "r->biteLeft(5): \"" << r << "\"" << endl << endl;
	
	xvr2::Mutex m;
	
	cout << m << endl;
	
	cout << "==== String comparisons ====" << endl;
	comparisons();
	return 0;
}

void comparisons(){
	String s1;
	String s2;
	String s3;
	String s4, s5;
	s1 = "1234";
	s2 = "hello";
	s3 = "XVR-2";
	s4 = "C++";
	s5 = "WORLD";
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;
	cout << "s4: " << s4 << endl;
	cout << "s5: " << s5 << endl;
	cout << "Compare..." << endl;
	cout << "s1.compare(s2):      " << s1.compare(s2) << endl;
	cout << "s1 == s2:            " << ((s1 == s2)?"yes":"no") << endl;
	cout << "s2.compare(s3):      " << s2.compare(s3) << endl;
	cout << "s2 == s3:            " << ((s2 == s3)?"yes":"no") << endl;
	cout << "s1 == 1234:          " << ((s1 == 1234)?"yes":"no") << endl;
	cout << "s1 == \"1234\":        " << ((s1 == "1234")?"yes":"no") << endl;
	cout << "s5 starts with \"WO\": " << ((s5.startsWith("WO"))?"yes":"no") << endl;
	cout << "s5 ends with \"RLD\":  " << ((s5.endsWith("RLD"))?"yes":"no") << endl;

	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;
	cout << "s4: " << s4 << endl;	
}
