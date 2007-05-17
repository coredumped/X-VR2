/* $Id$ */
#include<xvr2/String.h>
#include<xvr2/StringBuffer.h>
#include<xvr2/ProcessRunner.h>
#include<xvr2/Tokenizer.h>
#include<xvr2/BufferedTextInputStream.h>
#include<iostream>

using xvr2::Platform::ProcessRunner;
using xvr2::Buffer;
using xvr2::String;
using xvr2::RawInputStream;
using xvr2::RawOutputStream;
using std::cout;
using std::cerr;
using std::endl;

const String &to_string(Buffer b){
	static String d;
	char buf[b.size() + 1];
	buf[b.size()] = 0;
	memcpy(buf, b.data(), b.size());
	d = buf;
	return d;
}

int main(int argc, char *argv[]){
	if(argc <= 1){
		cout << "At least you must specify a SMTP server address, PLEASE!!!!" << endl;
		return 1;
	}
	xvr2::StringBuffer cmdline;
	cmdline << "/usr/bin/telnet " << argv[1] << " 25";
	ProcessRunner smtp_client(cmdline.toString());
	smtp_client.start();
	xvr2::BufferedTextInputStream out(smtp_client.outputStream(), "\n");
	xvr2::BufferedTextInputStream err(smtp_client.errorStream());
	RawOutputStream in  = smtp_client.inputStream();
	cout << "Waiting for remote output..." << endl;
	String lastline;
	do{
		out >> lastline;
		cout << "GOT: " << lastline;
		cout.flush();
	}while(!lastline.startsWith("220"));
	cout << "== JUST GOT THE BANNER, SENDING SOME DATA..." << endl;
	xvr2::Tokenizer t1(lastline, " ");
	t1.next();
	String server = t1.next();
	xvr2::StringBuffer  outline;
	outline << "HELO " << server << "\n";
	cout << "SEND: " << outline.toString() << endl;
	in << outline.toString();
	outline.clear();
	do{
		out >> lastline;
		cout << "GOT: " << lastline;
		cout.flush();
	}while(!lastline.startsWith("250"));
	outline << "quit\n";
	in << outline.toString();
	cout << "SEND: " << outline.toString() << endl;
	do{
		out >> lastline;
		cout << "GOT: " << lastline;
		cout.flush();
	}while(!lastline.startsWith("221"));

	int retcode = -1;
	try{
		retcode = smtp_client.wait();
	}
	catch(xvr2::Platform::ProcessException e1){
		cout << e1.toString() << endl;
		cout << e1.message() << endl;
		cout << e1.comment() << endl;
	}
	cout << "Terminated with code: " << retcode << endl;
	return 0;
}

