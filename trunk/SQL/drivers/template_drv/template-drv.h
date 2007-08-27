/* $Id:template-drv.h 540 2007-08-20 07:51:56Z mindstorm2600 $ */
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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

