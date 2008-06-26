/*
 * $Id:pgsql-drvng.h 540 2007-08-20 07:51:56Z mindstorm2600 $
 *
 * X-VR2 
 * 
 * Copyright (C) Juan V. Guerrero 2007
 * 
 * Juan V. Guerrero <mindstorm2600@users.sourceforge.net>
 * 
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */
#ifndef __XVR2_PGSQL_DRV_NG_H__
#define __XVR2_PGSQL_DRV_NG_H__
#include"xvr2/SQL/Field.h"
#include"xvr2/SQL/ResultSet.h"
#include"xvr2/SQL/Driver.h"

using namespace xvr2::SQL;
using xvr2::String;

class PostgreSQLDriver : public Driver {
	private:
		xvr2::SQL::DriverInfo *dinfo;
	protected:
	public:
		PostgreSQLDriver();
		~PostgreSQLDriver();
		const xvr2::SQL::DriverInfo &getVersionInfo();
		void *connect(const xvr2::String &server, const xvr2::String &__dbname,	
						const xvr2::String &user, const xvr2::String &pass, 
						int port = 0);
		void *connect(const String &dbsock, 
						const String &_dbname, const String &_user, 
						const String &_pass);
		void *open(const String &dbfile);
		xvr2::SQL::ResultSet *query(void *__conn_handle, const xvr2::String &command);
		int execCommand(void *__conn_handle, const xvr2::String &command);
		bool disconnect(void *__conn_handle);
		void setAutoCommit(bool val = true);
		void commit(void *__conn_handle);
		const int numRows(void *__res_handle);
		const int numCols(void *__res_handle);
		xvr2::SQL::Field *fetchRow(void *__res_handle);
		const bool freeResultSet(void *__res_handle);
		const bool bulkBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim);
		const bool bulkAddData(void *conn_handle, const char *data, const char *delim);
		const bool bulkEnd(void *conn_handle);
		const bool bulkDownloadBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim);
		const bool bulkDownloadData(void *conn_handle, xvr2::String &data);
		const bool bulkDownloadEnd(void *conn_handle);
		char *quoteString(const char *str);
		xvr2::String escapeString(const xvr2::String &s);
		xvr2::String escapeString(const xvr2::String &s, void *conn_handle);
		const char *errorMessage(void *conn_handle);
		const char *resultErrorMessage(void *res_handle);
		const bool isConnected(void *conn_handle);
		const bool hasConnPolling();
};

extern "C" {
	PostgreSQLDriver *create_dbdriver_instance();
	void destroy_dbdriver_instance(PostgreSQLDriver *obj);
};

#endif
