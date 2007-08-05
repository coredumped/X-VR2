#include<xvr2/String.h>
#include<xvr2/Mutex.h>
#include<xvr2/ThreadManager.h>
#include<xvr2/Thread.h>
#include<xvr2/SharedVar.h>
#include<iostream>

using namespace xvr2;

Mutex om;

SharedVar<int> tnum;

class Prime:public Thread {
	private:
		int f, t;
	public:
		Prime(int _f, int _t){
			f = _f;
			t = _t;
		}
		void run();
};

void Prime::run(){
	int i, j;
	bool flag;
	String output;
	tnum++;
	output = "Prime numbers from ";
	output += f;
	output += " to ";
	output += t;
	output += ":\n";
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
	Prime *a;
	Prime *b;
	Prime *c;
	tnum.setValue(0);

	a = new Prime(10000, 12000);
	b = new Prime(20000, 22000);
	c = new Prime(60000, 61000);

	a->start();
	b->start();
	c->start();
	while(ThreadManager::activeCount() == 0);

	while(ThreadManager::activeCount() > 0){
		usleep(10);
	}
	return 0;
}
