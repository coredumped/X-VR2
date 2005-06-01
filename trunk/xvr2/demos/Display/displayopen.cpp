/* $Id$ */
/* TODO
 * Parse command-line arguments in order to permit the user to load the driver
 * he/she wants */
#include<xvr2.h>
#include<xglDisplay.h>

using namespace std;
using namespace xvr2;
using namespace xvr2::gl;

static char *driver_path = "/usr/local/lib/xvr2/xvr2_sdl_driver.so.0.0.1";

int main(int argc, char *argv[]){
	Display *x;
	void *instance = 0x0;
	int retcode = 0;
	try{
		cout << "Opening an 800x600 @ 24 bits display for 5 seconds...";
		cout.flush();
       		x = new Display(driver_path, 800, 600, 24);
		x->open(true);
		sleep(5);
		x->close();
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
