#include<xvr2.h>

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
		void *run();
};


void *Prime::run(){
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
	return 0;
}

int main(){
	Prime *a;
	Prime *b;
	Prime *c;
	tnum.setValue(0);

	a = new Prime(1000, 1200);
	b = new Prime(2000, 2200);
	c = new Prime(6000, 6100);

	ThreadManager::start(a);
	ThreadManager::start(b);
	ThreadManager::start(c);
	sleep(5);
	while(tnum.getValue() > 0){
		sleep(1);
	}
	return 0;
}
