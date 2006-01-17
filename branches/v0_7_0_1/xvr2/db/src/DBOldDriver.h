/*
 * $Id$
 */
#ifndef __XVR2_DB_OLD_DRIVER_H__
#define __XVR2_DB_OLD_DRIVER_H__
#include<xvr2/Plugin.h>
#include<xvr2/DBDriver.h>
#include<xvr2/DBDriverInfo.h>
#include<xvr2/DBField.h>
#include<xvr2/DBResultSet.h>

namespace xvr2{

	namespace DB {

		class ResultSet;
		//class BasicDriver;
	
		/**
		 * This class is an abstract interface for dynamic loading 
		 * database driver objects
		 *
		 */
		class OldDriver:public xvr2::DB::Driver {
			private:
			protected:
				/** This is the driver handle */
				Plugin *__drv;
				bool		__do_auto_commit;
				bool		(*__drv_init)(OldDriver *__me);
				bool		(*__drv_cleanup)();
				void		*(*__drv_connect)(const char *srvr, 
								  const char *dbname, 
								  const char *usr, 
								  const char *pass, 
								  const int port);
				UInt32		(*__drv_disconnect)(void *handle);
				bool		(*__drv_getVersionInfo)(DB::DriverInfo **i);
				bool		(*__drv_commit)(void *handle);
				ResultSet	*(*__drv_query)(void *handle, 
								const char *cmd);
				// The following method pointers are for ResultSet usage
				Field	*(*__drv_fetch_next_row)(void *__res_handle);
				int		(*__drv_numcols)(void *__res_handle);
				int		(*__drv_numrows)(void *__res_handle);
				bool		(*__drv_free_resultset)(void *__res_handle);
				bool		(*__drv_bulk_begin)(void *conn_handle, const char *table, const char *cols, const char *delim);
				bool		(*__drv_bulk_insert)(void *conn_handle, const char *data, const char *delim);
				bool		(*__drv_bulk_end)(void *conn_handle);
				bool		__is_loaded;
				bool 		has__drv_bulk_begin;
				bool 		has__drv_bulk_insert;
				bool 		has__drv_bulk_end;

				char		*(*__drv_quote_string)(const char *in);
				char 		*(*__drv_error_message)(void *handle);
				char 		*(*__drv_result_error_message)(void *r);

				// Connection status polling
				bool		(*__drv_connected)(void *conn_handle);
				bool		has_conn_polling;
			public:
				/** Default constructor it initialzes some 
				 *  defaults only */
				OldDriver(const String &soname);
				/** Destructor, this will verify if the 
				 *  Driver class is still loaded, if 
				 *  it is then it will unload it and 
				 *  attempt to clear all used resources */
				virtual ~OldDriver();
				/** This will load the class and any 
				 *  required internal symbols */
				void load();
				/** Use this function to retrieve verion 
				 *  and/or vendor informaton for the 
				 *  driver */
				void getVersionInfo(DB::DriverInfo **info);
			    virtual const DB::DriverInfo &getVersionInfo(){
					static DriverInfo a;
					return a;
				}
				/** Driver supplied database connection 
				 *  function, it will return a <b>handler</b>
				 *  to the current connection if it is 
				 *  successfull.
				 *  The parameter <b>server</b> stands for
				 *  the server IP address or hostname.
				 *  <b>user</b> is the username as to whom
				 *  be connected, <b>pass</b> is the password
				 *  to be used and <b>port</b> is the port
				 *  to be used if there is a need to specify it
				 *  if you send the default <b>0</b> then the
				 *  port used is going to be the default for
				 *  the backend database.
				 */
				virtual void *connect(const String &server, 
						      const String &__dbname,
						      const String &user, const String &pass,
						      int port = 0);
				/** Use this method to send a command to 
				 *  the backend server. <b>__handle</b> is
				 *  the connection handler and <b>command</b>
				 *  is the command to be send to the backend
				 *  database */
				virtual ResultSet *query(void *__handle, 
							 const String &command);
				/** This method will disconnect you from 
				 *  the backend server if you are 
				 *  connected */
				virtual bool disconnect(void *__handle);
				/** The use of this method will turn on 
				 *  autocommits, the idea is that if you 
				 *  issue an  update or delete command this 
				 *  will call the commit command 
				 *  inmediately so there is no reason for 
				 *  you to call it manually everytime 
				 *  you need it */
				virtual void setAutoCommit(bool val = true);
				/** This will commit any transaction based 
				 *  command to the database, when you call 
				 *  commit every submitted delete or update 
				 *  they will execute each other in 
				 *  sequence */
				virtual void commit(void *__handle);
				/** This will return the number of rows for the current
				 *  result handle */
				virtual const int numRows(void *__res_handle);
				/** This will return the number of columns for the current
				 *  result handle */
				virtual const int numCols(void *__res_handle);
				/** This will fetch a row of data from a result obtained
				 *  after issueing a query to the RDBMS */
				Field *fetchRow(void *__res_handle);
				/** This will provide a means for clearing the memory used
				 *  by the resultset, this method must be call to release
				 *  that memory and avoid a memory leak */
				const bool freeResultSet(void *__res_handle);
				/** Call this method to start a bulk loading process.
				 *  Bulk load is a process provided by many RDBMSs where
				 *  you can load big amounts of data without requiring to
				 *  perform a lot of insert commands, this method is usually
				 *  faster and recommended in scenarios where you load data
				 *  which is contained in files, like .csv stuff
				 *  \param conn_handle The connection handle
				 *  \param tablename The table where you want to upload your data
				 *  \param cols A comma delimited list of column names specifiying
				 *  \param delim The string used to separate every field
				 *  which columns are to be affected by the operation. */
				virtual const bool bulkBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim);
				/** Use this method to actually load data during a bolk load process
				 *  started by the bulkBegin method.
				 *  \param conn_handle Connection handle
				 *  \param data The data to be loaded, every field must be delimited
				 *  \param delim The string used to separate every field
				 *  as previuosly specified during the bulkBegin method call. */
				virtual const bool bulkAddData(void *conn_handle, const char *data, const char *delim);
				/** Flushes all data sent by bulkAddData and tells the server to actually
				 *  insert it into the table.
				 *  \param conn_handle The connection handle */
				virtual const bool bulkEnd(void *conn_handle);
				/** Quotes a string to be passed in an SQL query this is neccesary since
				 *  some chars can confuse the SQL command parser in the RDBMS, after 
				 *  calling this method you must free all memory allocated from the it.
				 *  \param str The string to be escaped
				 *  \return The escaped string, you must free this pointer after used */
				virtual char *quoteString(const char *str);
				/** Returns a specific error message returned by the latest operation
				 *  executed at the connection level.
				 *  \param conn_handle The connection handle
				 *  \return The error string*/
				virtual const char *errorMessage(void *conn_handle);
				/** Returns a specific error message returned by the latest operation
				 *  executed at the query's ResultSet level.
				 *  \param res_handle The ResultSet handle
				 *  \return The error string*/
				virtual const char *resultErrorMessage(void *res_handle);
				virtual const bool isConnected(void *conn_handle);
				const bool hasConnPolling(){
					return has_conn_polling;
				}
		};
	};
};

#endif
