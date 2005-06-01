#include<xvr2.h>

using namespace xvr2;
using namespace std;

int main(int argc, char *argv[]){
	String s1;
	String s2;
	String s3;
	String s4;
	s1 = "1234";
	s2 = "hello";
	s3 = "XVR-2";
	s4 = "C++";
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;
	cout << "s4: " << s4 << endl;
	cout << "Compare..." << endl;
	cout << "s1.compare(s2)\t" << s1.compare(s2) << endl;
	cout << "s1 == s2:\t" << ((s1 == s2)?"yes":"no") << endl;
	cout << "s2.compare(s3)\t" << s2.compare(s3) << endl;
	cout << "s2 == s3:\t" << ((s2 == s3)?"yes":"no") << endl;
	cout << "s1 == 1234:\t" << ((s1 == 1234)?"yes":"no") << endl;


	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;
	cout << "s4: " << s4 << endl;
	return 0;
}
