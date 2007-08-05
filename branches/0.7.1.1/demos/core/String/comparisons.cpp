#include<xvr2/String.h>
#include<iostream>

using namespace xvr2;
using namespace std;

int main(int argc, char *argv[]){
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
	return 0;
}
