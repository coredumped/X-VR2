/* $Id$ */
#ifndef __XVR2_DB_TEMPLATE_DRV_NG_H__
#define __XVR2_DB_TEMPLATE_DRV_NG_H__
#include<xvr2/DBField.h>
#include<xvr2/DBResultSet.h>
#include<xvr2/DBDriver.h>

using namespace xvr2::DB;
using xvr2::String;

class DB_TemplateDriver : public Driver {
	private:
		DriverInfo *dinfo;
	protected:
	public:
		DB_TemplateDriver();
		~DB_TemplateDriver();
		const DriverInfo &getVersionInfo();
		void *connect(const String &server, const String &__dbname, const String &user, const String &pass, int port = 0);
		ResultSet *query(void *__conn_handle, const String &command);
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
		char *quoteString(const char *str);
		String escapeString(const String &s);
		String escapeString(const String &s, void *conn_handle);
		const char *errorMessage(void *conn_handle);
		const char *resultErrorMessage(void *res_handle);
		const bool isConnected(void *conn_handle);
		const bool hasConnPolling();
};

extern "C" {
	DB_TemplateDriver *create_dbdriver_instance();
	void destroy_dbdriver_instance(DB_TemplateDriver *obj);
};

#endif

