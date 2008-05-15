/*
 * $Id$
 */
#ifndef __XVR2_DB_DRIVER_H__
#define __XVR2_DB_DRIVER_H__
 

#include<xvr2/xvr2config.h>
#include<xvr2/DBDriverInfo.h>


namespace xvr2 {
	namespace DB {
		class ResultSet;
		class Field;

		/* Interface class for database drivers */
		class Driver:public Object {
			private:
			protected:
			public:
				bool conn_requires_lock;
				bool query_requires_lock;
				bool bulk_requires_specific_lock;
				bool resultset_requires_lock;
				Driver();
				/** Use this function to retrieve verion 
				 *  and/or vendor informaton for the 
				 *  driver */
				virtual const DB::DriverInfo &getVersionInfo() = 0;
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
						      int port = 0) = 0;
				/** Use this method to send a command to 
				 *  the backend server. <b>__handle</b> is
				 *  the connection handler and <b>command</b>
				 *  is the command to be send to the backend
				 *  database */
				virtual ResultSet *query(void *__handle, 
							 const String &command) = 0;
				/** Use this method to send a command to 
				 *  the backend server. <b>__handle</b> is
				 *  the connection handler and <b>command</b>
				 *  is the command to be send to the backend
				 *  database. The command is question must NOT
				 *  return any rows, this method is intended to
				 *  be used only for execution, commands like
				 *  DELETE, UPDATE, INSERT, etc. */
				virtual int execCommand(void *__handle, 
							 const String &command) = 0;
				/** This method will disconnect you from 
				 *  the backend server if you are 
				 *  connected */
				virtual bool disconnect(void *__handle) = 0;
				/** The use of this method will turn on 
				 *  autocommits, the idea is that if you 
				 *  issue an  update or delete command this 
				 *  will call the commit command 
				 *  inmediately so there is no reason for 
				 *  you to call it manually everytime 
				 *  you need it */
				virtual void setAutoCommit(bool val = true) = 0;
				/** This will commit any transaction based 
				 *  command to the database, when you call 
				 *  commit every submitted delete or update 
				 *  they will execute each other in 
				 *  sequence */
				virtual void commit(void *__handle) = 0;
				/** This will return the number of rows for the current
				 *  result handle */
				virtual const int numRows(void *__res_handle) = 0;
				/** This will return the number of columns for the current
				 *  result handle */
				virtual const int numCols(void *__res_handle) = 0;
				/** This will fetch a row of data from a result obtained
				 *  after issueing a query to the RDBMS */
				virtual Field *fetchRow(void *__res_handle) = 0;
				/** This will provide a means for clearing the memory used
				 *  by the resultset, this method must be call to release
				 *  that memory and avoid a memory leak */
				virtual const bool freeResultSet(void *__res_handle) = 0;
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
				virtual const bool bulkBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim) = 0;
				/** Use this method to actually load data during a bolk load process
				 *  started by the bulkBegin method.
				 *  \param conn_handle Connection handle
				 *  \param data The data to be loaded, every field must be delimited
				 *  \param delim The string used to separate every field
				 *  as previuosly specified during the bulkBegin method call. */
				virtual const bool bulkAddData(void *conn_handle, const char *data, const char *delim) = 0;
				/** Flushes all data sent by bulkAddData and tells the server to actually
				 *  insert it into the table.
				 *  \param conn_handle The connection handle */
				virtual const bool bulkEnd(void *conn_handle) = 0;
				virtual const bool bulkDownloadBegin(void *conn_handle, const char *tablename, const char *cols, const char *delim) = 0;
				virtual const bool bulkDownloadData(void *conn_handle, xvr2::String &data) = 0;
				virtual const bool bulkDownloadEnd(void *conn_handle) = 0;
				/** \deprecated Please use String escapeString(const String &s, void *conn_handle);
				 *  Quotes a string to be passed in an SQL query this is neccesary since
				 *  some chars can confuse the SQL command parser in the RDBMS, after 
				 *  calling this method you must free all memory allocated from the it.
				 *  \param str The string to be escaped
				 *  \return The escaped string, you must free this pointer after used */
				virtual char *quoteString(const char *str) = 0;
				/** \deprecated Please use String escapeString(const String &s, void *conn_handle);
				 *  Quotes a string to be passed in an SQL query this is neccesary since
				 *  some chars can confuse the SQL command parser in the RDBMS, after 
				 *  calling this method you must free all memory allocated from the it.
				 *  \param str The string to be escaped
				 *  \return The escaped string, you must free this pointer after used */
				virtual String escapeString(const String &s) = 0;
				/** Quotes a string to be passed in an SQL query this is neccesary since
				 *  some chars can confuse the SQL command parser in the RDBMS, after 
				 *  calling this method you must free all memory allocated from the it.
				 *  \param str The string to be escaped
				 *  \param conn_handle The RDBMS connection from where you're connecting
				 *  \return The escaped string, you must free this pointer after used */
				virtual String escapeString(const String &s, void *conn_handle) = 0;

				/** Returns a specific error message returned by the latest operation
				 *  executed at the connection level.
				 *  \param conn_handle The connection handle
				 *  \return The error string*/
				virtual const char *errorMessage(void *conn_handle) = 0;
				/** Returns a specific error message returned by the latest operation
				 *  executed at the query's ResultSet level.
				 *  \param res_handle The ResultSet handle
				 *  \return The error string*/
				virtual const char *resultErrorMessage(void *res_handle) = 0;
				/** Verifies wheter the connection is still live or not. */
				virtual const bool isConnected(void *conn_handle) = 0;
				/** Says if the driver's connection can be polled for connection or not. */
				virtual const bool hasConnPolling() = 0;
		};
	};
};

#endif
