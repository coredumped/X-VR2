/*
 * $Id$
 */
#ifndef __PGSQL_DRIVER_H__
#define __PGSQL_DRIVER_H__

#include<xvr2/DBResultSet.h>
#include<xvr2/DBField.h>
#include<xvr2/DBDriver.h>
#include<xvr2/DataTypes.h>
#include<xvr2/NullPointerException.h>
#include<xvr2/Mutex.h>
#include<xvr2/Memory.h>

extern "C" { 
/** 
 * \fn bool	__drv_init(xvr2::DB::SQLDriver *__me)
 * \brief This function initializes the driver itself taking as an argument the parent 
 * SQLDriver class which is trying to generate it.
 * It must first verify that this pointer is not null, then call any client RDBMS
 * initialization methods and finally filling the <b>info</b> DBDriverInfo object
 * with data appropiate for the current driver implementation.
 * \param __me A pointer the driver object who invoqued this driver*/
bool			__drv_init(xvr2::DB::Driver *__me);
bool			__drv_cleanup();
void 			*__drv_connect(const char *srvr, const char *dbname, const char *usr, const char *pass, const int port);
UInt32 			__drv_disconnect(void *handle);
bool			__drv_getVersionInfo(xvr2::DB::DriverInfo **i);
bool			__drv_commit(void *handle);
xvr2::DB::ResultSet	 *__drv_query(void *handle, const char *cmd);
bool			__drv_usedb(void *handle, const char *dbname);
xvr2::DB::Field 	*__drv_fetch_next_row(void *handle);
int			__drv_numcols(void *handle);
int			__drv_numrows(void *handle);
bool			__drv_free_resultset(void *handle);

bool			__drv_bulk_begin(void *conn_handle, const char *tablename, const char *columns, const char *delim);
bool			__drv_bulk_insert(void *conn_handle, const char *data, const char *delim);
bool			__drv_bulk_end(void *conn_handle);

char			*__drv_quote_string(const char *in);
char 			*__drv_error_message(void *handle);
char 			*__drv_result_error_message(void *r_handle);

};


#endif
