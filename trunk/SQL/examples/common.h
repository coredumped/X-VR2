#include<xvr2/DB/DriverManager.h>
#include<xvr2/Tokenizer.h>
#include<xvr2/DB/Connection.h>
#include<xvr2/DB/Field.h>
#include<xvr2/DB/ResultSet.h>
#include<xvr2/DB/Driver.h>
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
