#ifndef __DB_DEMO_COMMON_H__
#define __DB_DEMO_COMMON_H__

enum demoType {
	XVR2_MYSQL,
	XVR2_POSTGRESQL,
	XVR2_SQLITE,
	XVR2_ORACLE,
	XVR2_SYBASE
};

bool parse_args(int argc, char *argv[]);
int rundemo(int demo_type);
#endif
