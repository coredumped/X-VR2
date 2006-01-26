/*
 * $Id$
 */
#ifndef __TEMPLATE_DRIVER_H__
#define __TEMPLATE_DRIVER_H__
#include<xvr2.h>

extern "C" { 
/** This function initializes the driver itself taking as an argument the parent 
 *  SQLDriver class which is trying to generate it.
 *  It must first verify that this pointer is not null, then call any client RDBMS
 *  initialization methods and finally filling the <b>info</b> DBDriverInfo object
 *  with data appropiate for the current driver implementation. */
bool	__drv_init(xvr2::SQLDriver *__me);
bool	__drv_cleanup();
void *__drv_connect(const char *srvr, const char *usr, const char *pass, const int port);
Uint32 __drv_disconnect(void *handle);
bool	__drv_getVersionInfo(xvr2::DBDriverInfo **i);
bool	__drv_commit(void *handle);
xvr2::ResultSet *__drv_query(void *handle, const char *cmd);
bool	__drv_usedb(void *handle, const char *dbname);
xvr2::SQLField *__drv_fetch_next_row(void *handle);
int	__drv_numcols(void *handle);
int	__drv_numrows(void *handle);
bool	__drv_free_resultset(void *handle);

};


#endif
