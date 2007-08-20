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
#ifndef __XVR2_SQL_DATABASE_EXCEPTION_H__
#define __XVR2_SQL_DATABASE_EXCEPTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>

namespace xvr2 {
	namespace SQL {
		class ResultSet;
		/** Generic database exception */
		class DatabaseException:public Exception{
			protected:
				String _err_msg;
			public:
				enum ConnectionType {
					NET,
					FIFO,
					EMBEDDED
				};
				struct ConnectionParams {
					DatabaseException::ConnectionType type;
					String host;
					int port;
					String username;
					String password;
					String database;
					String path;
					ConnectionParams();
					ConnectionParams(DatabaseException::ConnectionType t,
									const String &h, int port, const String &db,
									const String &u, const String &p,
									const String &_path = "");
					ConnectionParams(const ConnectionParams &c);
					ConnectionParams &operator=(const ConnectionParams &c);
				};
				/**
				 * Default constructor
				 */
				DatabaseException();
				DatabaseException(const String &error_message);
				DatabaseException(const String &error_message, 
									const ConnectionParams &__conn_p);
				DatabaseException(const ConnectionParams &__conn_p);
				/** @brief Gets the connection parameters used at the time of 
				 *  failure. 
				 *  @return A ConnectionFailure::ConnectionParams object 
				 *  containing the details of the connection failure.
				 *  @warning The password field will always be left blank
				 *  unless you explicitly allow support for displaying it by 
				 *  calling enablePasswordDisplay. */
				const ConnectionParams &connParams();
				/** @brief Gives an specific error message regarding the reason
				 *  why this exception was thrown.
				 *  Depending from where the exception was thrown it is quite
				 *  possible that the message might even be generated at driver
				 *  level which is good since it will give more accurate 
				 *  information.
				 *  @return The error message itself */
				const String &errorMessage();
			protected:
				ConnectionParams _conn_params;
		};
		
		/** @brief Thrown when a unsupported operation has been requested to 
		 *  the underliying SQL driver. */
		class DriverOperationNotSupported : public DatabaseException {
			private:
				String op;
			public:
				DriverOperationNotSupported();
				DriverOperationNotSupported(const String &_op);
				/** @brief The name of the failed operation. */
				const String &operation();
		};


		/** Unable to reach the database server */
		class DBServerUnreachable:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				DBServerUnreachable();
		};


		/** An attempt to reconnect using the same connection failed because you are already connected */
		class AlreadyConnected2DB:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				AlreadyConnected2DB();
		};


		/** In order to complete the current command to the SQL backend, please connect to the backend first */
		class DBConnectFirst:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				DBConnectFirst();
		};

		/** Unable to complete the operation until you do a fetchRow first, sorry */
		class NoDataFetch:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				NoDataFetch();
		};


		/** There are no more rows to fetch from this ResultSet */
		class NoMoreRows:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				NoMoreRows();
		};


		/** @brief Exception thrown whenever a database connection fails.
		 *  @deprecated Is going to be replaced by xvr2::DB::ConnectionFailure
		 *  @todo Replace with ConnectionFailure. */
		class DBConnectionFailed:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				DBConnectionFailed();
		};
		
		/** @brief Exception thrown whenever a connection attempt to a remote
		 *  database fails. */
		class ConnectionFailure:public DatabaseException{
			private:
			public:
				ConnectionFailure();
				ConnectionFailure(const ConnectionParams &__conn_p);
				ConnectionFailure(const ConnectionParams &__conn_p, 
									const String &__cause);
		};


		/** There was a sudden disconnection from the RDBMS */
		class ServerDisconnected:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				ServerDisconnected();
		};

		/** @todo Document FieldIsNull exception's description */
		class FieldIsNull:public  DatabaseException {
			private:
				String field_name;
			public:
			/** This exception is thrown whenever a field which is
			 *  NULL dows not have a direct conversion to a specified
			 *  data type, eg NULL -> TIME. However this is not true for
			 *  string covnersions since it is permissible to have a
			 *  NULL mapped to a "". */
				FieldIsNull();
				FieldIsNull(const String &fn);
				const String &fieldName();
		};


		/** Generic SQL query exception */
		class SQLQueryException:public DatabaseException{
			private:
				SQL::ResultSet *result;
				String _query;
			public:
				/**
				 * Default constructor
				 */
				SQLQueryException();
				~SQLQueryException();
				SQLQueryException(const char *msg);
				SQLQueryException(const char *msg, const String &__query);
				SQLQueryException(const char *msg, SQL::ResultSet *_result);
				SQLQueryException(const char *msg, SQL::ResultSet *_result, const String &__query);
				const String &query();
		};


		/** For some reason the server got disconnected while executing the underlying query. */
		class SQLQueryRDBMSDisconnected:public SQLQueryException{
			public:
				/**
				 * Default constructor
				 */
				SQLQueryRDBMSDisconnected();
		};

		/** The SQL query sentece provide was not compatible or understandable
		 * to the RDBMS engine, please provide an appropiate SQL query with escape
		 * secuences were needed */
		class UnableToParseQuery:public SQLQueryException{
			public:
				/**
				 * Default constructor
				 */
				UnableToParseQuery();
		};

		class BulkUploadFailed:public SQLQueryException{
			public:
				/**
				 * Default constructor
				 */
				BulkUploadFailed();
		};

		class BulkDataParse:public SQLQueryException{
			public:
				/**
				 * Default constructor
				 */
				BulkDataParse();
		};

		class BulkUploadStart:public SQLQueryException{
			public:
				/**
				 * Default constructor
				 */
				BulkUploadStart();
		};
	};
};

#endif

