#include<xvr2/String.h>
#include<xvr2/Console.h>

using xvr2::String;
using xvr2::Console;

Console con;

String func1(){
	String a("hola");
	return a;
}

String func2(){
	String a("hola");
	return String("demonios");
}

int main(){
	String main("hello world"), sub;
	con << func1() << "\n";
	con << func2() << "\n";
	sub = main.getSubstr(0, 5);
	con << sub << "\n";
	return 0;
}
