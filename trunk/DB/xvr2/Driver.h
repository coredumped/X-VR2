/*
 * $Id$
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
#ifndef __XVR2_DB_DRIVER_H__
#define __XVR2_DB_DRIVER_H__
 

#include<xvr2/xvr2config.h>
#include<xvr2/DB/DriverInfo.h>


namespace xvr2 {
	namespace DB {
		class ResultSet;
		class Field;

		/* @brief Interface class for database drivers. */
		class Driver:public Object {
			private:
			protected:
			public:
				/** @internal A flag that specifies wheter a explicit mutex
				 *  should be used when allocating multiple connection
				 *  concurrently. */
				bool conn_requires_lock;
				/** @internal A flag that says wheter or not a explict mutex
				 *  lock is required at the time a SQL query is to be exectuted */
				bool query_requires_lock;
				bool bulk_requires_specific_lock;
				bool resultset_requires_lock;
				Driver();
				/** @brief Use this function to retrieve version and/or vendor 
				 *  informaton for the driver. */
				virtual const DB::DriverInfo &getVersionInfo() = 0;
				/** @brief Attempts to make a connection the specified database
				 *  server.
				 *  Driver supplied database connection function, it will try
				 *  to make a remote (networked) connection to the database
				 *  server.
				 *  @param server Should be the server's IP address or hostname
				 *  @param __dbname Database name to connect to.
				 *  @param user Username to connect to the database as
				 *  @param pass User's login password
				 *  @param port Connection port, if 0, then the driver will use
				 *  the default connection port for the specified database.
				 *  @return A connection handler. */
				virtual void *connect(const String &server, 
						      const String &__dbname,
						      const String &user, const String &pass,
						      int port = 0) = 0;
				/** @brief Attempts to make a connection to a local database 
				 *  instance.
				 *  Driver supplied database connection function, it will try 
				 *  to connect to a locally running database instance, commonly
				 *  this is performed by connection to a FIFO file.
				 *  @param dbsock FIFO file to open for connection.
				 *  @param _dbname Database name to connect to.
				 *  @param _user Username to connect to the database as
				 *  @param _pass User's login password
				 *  @return A connection handler. */
				virtual void *connect(const String &dbsock, 
								const String &_dbname, const String &_user, 
								const String &_pass) = 0;
				/** @brief Opens a connection to a local (embedded) database
				 *  engine.
				 *  Driver supplied database connection function, this method
				 *  will attempt to open a datafile as if it was a networked
				 *  connection, this is very useful for embedded database
				 *  engines which implement the SQL query language.
				 *  @param dbfile A path to the datafile to the opened.
				 *  @return A connection handler. */
				virtual void *open(const String &dbfile) = 0;
				/** Use this method to send a command to 
				 *  the backend server.
				 *  @param __handle Connection handler as returned from connect
				 *  @param command The command to be send to the backend
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
				/** \deprecated Please use String escapeString(const String &s, void *conn_handle);
				 *  Quotes a string to be passed in an SQL query this is neccesary since
				 *  some chars can confuse the SQL command parser in the RDBMS, after 
				 *  calling this method you must free all memory allocated from the it.
				 *  \param str The string to be escaped
				 *  \return The escaped string, you must free this pointer after used */
				virtual char *quoteString(const char *str) = 0;
				/** @deprecated Please use String escapeString(const String &s, void *conn_handle);
				 *  Quotes a string to be passed in an SQL query this is neccesary since
				 *  some chars can confuse the SQL command parser in the RDBMS, after 
				 *  calling this method you must free all memory allocated from the it.
				 *  @param s The string to be escaped
				 *  @return The escaped string, you must free this pointer after used */
				virtual String escapeString(const String &s) = 0;
				/** Quotes a string to be passed in an SQL query this is neccesary since
				 *  some chars can confuse the SQL command parser in the RDBMS, after 
				 *  calling this method you must free all memory allocated from the it.
				 *  @param s The string to be escaped
				 *  @param conn_handle The RDBMS connection from where you're connecting
				 *  @return The escaped string, you must free this pointer after used */
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
