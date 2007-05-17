/* $Id: loader.cpp,v 1.2 2005/06/04 13:15:35 mindstorm2600 Exp $ */
/* TODO
 * Parse command-line arguments in order to permit the user to load the driver
 * he/she wants */
#include<xvr2.h>
#include<xglDisplayDriver.h>

using namespace std;
using namespace xvr2;
using namespace xvr2::gl;

static char *driver_path = __XVR2_PREFIX_DIR "/lib/xvr2/xvr2_sdl_driver.so." __XVR2_VERSION_STRING;

int main(int argc, char *argv[]){
	DisplayDriver *x;
	void *instance = 0x0;
	int retcode = 0;
	try{
		cout << "Using: " << driver_path << "..." << endl;
       		x = new DisplayDriver(driver_path);
		cout << "Initializing... ";
		cout.flush();
		instance = x->init();
		if(instance == 0x0){
			cerr << "failure" << endl;
			retcode = 1;
		}
		else{
			cout << "success" << endl;
		}
		cout << "Deallocating... ";
		cout.flush();
		xvr2_delete(x);
		cout << "done" << endl;
	}
	catch(Exception::Exception e){
		cerr << "Operation failed: " << e.toString() << endl;
	}
	return retcode;
}
