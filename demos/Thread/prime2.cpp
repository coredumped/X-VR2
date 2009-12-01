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
		void joinTo(Prime *to);
		void *run();
};

Prime *a;
Prime *b;
Prime *c;

void Prime::joinTo(Prime *to){
	to->join();
}

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
	if(this == b)
		c->join();
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
	tnum.setValue(0);

	a = new Prime(10000, 120000);
	b = new Prime(20000, 220000);
	c = new Prime(60000, 610000);

	a->start();
	b->start();
	c->start();
	while(ThreadManager::activeCount() == 0);
	while(tnum.getValue() > 0){
		usleep(1);
	}
	return 0;
}
