/*
 * $Id:DatabaseException.h 531 2007-08-11 09:05:29Z mindstorm2600 $
 */
#ifndef __XVR2_DATABASE_EXCEPTION_H__
#define __XVR2_DATABASE_EXCEPTION_H__
#include<xvr2/xvr2config.h>
#include<xvr2/CoreExceptions.h>
#include<xvr2/String.h>

namespace xvr2 {
	namespace DB {
		class ResultSet;
		/** Generic database exception */
		class DatabaseException:public Exception{
			public:
				/**
				 * Default constructor
				 */
				DatabaseException();
				DatabaseException(const String &error_message);
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


		/** Unable to connect to the specified database server */
		class DBConnectionFailed:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				DBConnectionFailed();
		};


		/** There was a sudden disconnection from the RDBMS */
		class ServerDisconnected:public DatabaseException{
			public:
				/**
				 * Default constructor
				 */
				ServerDisconnected();
		};

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
				DB::ResultSet *result;
				String _query;
			public:
				/**
				 * Default constructor
				 */
				SQLQueryException();
				~SQLQueryException();
				SQLQueryException(const char *msg);
				SQLQueryException(const char *msg, const String &__query);
				SQLQueryException(const char *msg, DB::ResultSet *_result);
				SQLQueryException(const char *msg, DB::ResultSet *_result, const String &__query);
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
