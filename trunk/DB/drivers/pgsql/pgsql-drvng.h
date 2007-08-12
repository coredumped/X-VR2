/* $Id$ */
#ifndef __XVR2_PGSQL_DRV_NG_H__
#define __XVR2_PGSQL_DRV_NG_H__
#include"xvr2/DB/Field.h"
#include"xvr2/DB/ResultSet.h"
#include"xvr2/DB/Driver.h"

using namespace xvr2::DB;
using xvr2::String;

class PostgreSQLDriver : public Driver {
	private:
		xvr2::DB::DriverInfo *dinfo;
	protected:
	public:
		PostgreSQLDriver();
		~PostgreSQLDriver();
		const xvr2::DB::DriverInfo &getVersionInfo();
		void *connect(const xvr2::String &server, const xvr2::String &__dbname,	const xvr2::String &user, const xvr2::String &pass, int port = 0);
		xvr2::DB::ResultSet *query(void *__conn_handle, const xvr2::String &command);
		int execCommand(void *__conn_handle, const xvr2::String &command);
		bool disconnect(void *__conn_handle);
		void setAutoCommit(bool val = true);
		void commit(void *__conn_handle);
		const int numRows(void *__res_handle);
		const int numCols(void *__res_handle);
		xvr2::DB::Field *fetchRow(void *__res_handle);
		const bool freeResultSet(void *__res_handle);
		const bool bulkBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim);
		const bool bulkAddData(void *conn_handle, const char *data, const char *delim);
		const bool bulkEnd(void *conn_handle);
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
