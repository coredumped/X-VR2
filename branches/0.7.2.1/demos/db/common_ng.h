#include<xvr2/DBDriverManager.h>
#include<xvr2/Tokenizer.h>
#include<xvr2/DBConnection.h>
#include<xvr2/DBField.h>
#include<xvr2/DBResultSet.h>
#include<xvr2/DBDriver.h>
#include<xvr2/DBCommand.h>
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
