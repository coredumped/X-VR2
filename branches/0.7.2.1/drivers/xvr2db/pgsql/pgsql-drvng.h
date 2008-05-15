/* $Id$ */
#ifndef __XVR2_PGSQL_DRV_NG_H__
#define __XVR2_PGSQL_DRV_NG_H__
#include<xvr2/DBField.h>
#include<xvr2/DBResultSet.h>
#include<xvr2/DBDriver.h>

using namespace xvr2::DB;
using xvr2::String;

class PostgreSQLDriver : public Driver {
	private:
		DriverInfo *dinfo;
	protected:
	public:
		PostgreSQLDriver();
		~PostgreSQLDriver();
		const DriverInfo &getVersionInfo();
		void *connect(const String &server, const String &__dbname, const String &user, const String &pass, int port = 0);
		ResultSet *query(void *__conn_handle, const String &command);
		int execCommand(void *__conn_handle, const String &command);
		bool disconnect(void *__conn_handle);
		void setAutoCommit(bool val = true);
		void commit(void *__conn_handle);
		const int numRows(void *__res_handle);
		const int numCols(void *__res_handle);
		Field *fetchRow(void *__res_handle);
		const bool freeResultSet(void *__res_handle);
		const bool bulkBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim);
		const bool bulkAddData(void *conn_handle, const char *data, const char *delim);
		const bool bulkEnd(void *conn_handle);
		const bool bulkDownloadBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim);
		const bool bulkDownloadData(void *conn_handle, xvr2::String &data);
		const bool bulkDownloadEnd(void *conn_handle);
		char *quoteString(const char *str);
		String escapeString(const String &s);
		String escapeString(const String &s, void *conn_handle);
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
