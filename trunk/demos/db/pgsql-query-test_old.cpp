#include"common.h"

using namespace xvr2;

#define DRIVER_LOCATION  __XVR2_PREFIX_DIR "/lib/xvr2/pgsql_driver.so"

int main(int argc, char *argv[]){
	parse_args(argc, argv);
	return rundemo(XVR2_POSTGRESQL);
}
