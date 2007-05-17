/*
 * $Id$
 */
#ifndef __MYSQL_DRIVER_H__
#define __MYSQL_DRIVER_H__

#include<DBResultSet.h>
#include<DBField.h>
#include<DBDriver.h>
#include<DataTypes.h>
#include<NullPointerException.h>
#include<Mutex.h>
#include<Memory.h>

extern "C" { 
/** 
 * \fn bool	__drv_init(xvr2::DB::SQLDriver *__me)
 * \brief This function initializes the driver itself taking as an argument the parent 
 * SQLDriver class which is trying to generate it.
 * It must first verify that this pointer is not null, then call any client RDBMS
 * initialization methods and finally filling the <b>info</b> DBDriverInfo object
 * with data appropiate for the current driver implementation.
 * \var __me This is a pointer the driver object who invoques this driver call*/
bool	__drv_init(xvr2::DB::Driver *__me);
bool	__drv_cleanup();
void *__drv_connect(const char *srvr, const char *dbname, const char *usr, const char *pass, const int port);
UInt32 __drv_disconnect(void *handle);
bool	__drv_getVersionInfo(xvr2::DB::DriverInfo **i);
bool	__drv_commit(void *handle);
xvr2::DB::ResultSet *__drv_query(void *handle, const char *cmd);
xvr2::DB::Field *__drv_fetch_next_row(void *handle);
int	__drv_numcols(void *handle);
int	__drv_numrows(void *handle);
bool	__drv_free_resultset(void *handle);
bool    __drv_usedb(void *handle, const char *dbname);

};


#endif
