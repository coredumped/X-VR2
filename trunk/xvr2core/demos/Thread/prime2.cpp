#include<xvr2/String.h>
#include<xvr2/SharedVar.h>
#include<xvr2/ThreadManager.h>
#include<xvr2/Thread.h>
#include<xvr2/JoinableThread.h>
#include<xvr2/Mutex.h>
#include<iostream>

using namespace xvr2;


Mutex om;

SharedVar<int> tnum;

class Prime:public JoinableThread {
	private:
		int f, t;
	public:
		Prime(int _f, int _t){
			f = _f;
			t = _t;
		}
		void joinTo(Prime *to);
		void run();
};

Prime *a;
Prime *b;
Prime *c;

void Prime::joinTo(Prime *to){
	ThreadManager::join(to);
}

void Prime::run(){
	int i, j;
	bool flag;
	String output;
	tnum++;
	//System::usleep(10000);
	output = "Prime numbers from ";
	output += f;
	output += " to ";
	output += t;
	output += ":\n";
	if(this == b)
		joinTo(c);
	for(i = f; i < t; i++){
		flag = true;
		for(j = 2; j < i; j++){
			if(i % j == 0){
				flag = false;
				break;
			}
		}
		if(flag){
			output += i;
			output += " ";
		}
	}
	om.lock();
	std::cout << output << std::endl;
	om.unlock();
	tnum--;
}

int main(){
	tnum.setValue(0);

	a = new Prime(10, 120);
	b = new Prime(20, 220);
	c = new Prime(60, 610);

	a->start();
	b->start();
	c->start();
	while(ThreadManager::activeCount() == 0);
	while(tnum.getValue() > 0){
		usleep(1);
	}
	return 0;
}
