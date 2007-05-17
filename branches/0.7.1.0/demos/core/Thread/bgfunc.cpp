#include<xvr2/String.h>
#include<xvr2/Console.h>
#include<xvr2/System.h>
#include<xvr2/SharedVar.h>
#include<xvr2/ThreadManager.h>
#include<xvr2/BackgroundFunction.h>

using xvr2::String;
using xvr2::System;
using xvr2::Console;
using xvr2::SharedVar;
using xvr2::ThreadManager;

class ping : public xvr2::BackgroundFunction {
	protected:
		String addr;
		SharedVar<bool> working;
	public:
		bool alive;
		ping(const String &ip){
			addr = ip;
			working = false;
			alive = false;
		}
		void operator()(){
			working = true;
			String cmd = "/bin/ping " + addr + " -c 1 -w 5 > /dev/null 2>&1";
			int ret = system(cmd.toCharPtr());
			if(ret == -1){
				debugmsgln(this, "Ping fork failed!!!!", __LINE__ - 2, __FILE__);
				throw xvr2::Exception();
			}
			else if(ret == 0){
				alive = true;
			}
			else {
				alive = false;
			}
			working = false;
		}
		bool finished(){
			return (working == true)?false:true;
		}
};



int main(int argc, char *argv[]){
	Console con;
	const char *spinner[] = {
		"/", "-", "\\", "|"
	};
	if(argc <= 1){
		con.errWriteLine("You must at least provide an address to be pinged.\n");
		return 1;
	}
	for(int i = 1, j = 0; i < argc; i++){
		ping p(argv[i]);
		con << argv[i] << " ";
		ThreadManager::start(p);
		while(!p.finished()){
			System::usleep(2000);
			con << spinner[(++j) % 4] << "\b";
		}
		if(p.alive){
			con << "is alive\n";
		}
		else{
			con << "no response\n";
		}
	}
	return 0;
}
