/*
 * $Id$
 */
#ifndef __XVR2_DATABASE_EXCEPTION_H__
#define __XVR2_DATABASE_EXCEPTION_H__
#include<Exception.h>

namespace xvr2 {
	namespace Exception{

		/** Generic database exception */
		class Database:public Exception{
			public:
				/**
				 * Default constructor
				 */
				Database();
		};


		/** Unable to reach the database server */
		class DBServerUnreachable:public Database{
			public:
				/**
				 * Default constructor
				 */
				DBServerUnreachable();
		};


		/** An attempt to reconnect using the same connection failed because you are already connected */
		class AlreadyConnected2DB:public Database{
			public:
				/**
				 * Default constructor
				 */
				AlreadyConnected2DB();
		};


		/** In order to complete the current command to the SQL backend, please connect to the backend first */
		class DBConnectFirst:public Database{
			public:
				/**
				 * Default constructor
				 */
				DBConnectFirst();
		};

		/** Unable to complete the operation until you do a fetchRow first, sorry */
		class NoDataFetch:public Database{
			public:
				/**
				 * Default constructor
				 */
				NoDataFetch();
		};


		/** There are no more rows to fetch from this ResultSet */
		class NoMoreRows:public Database{
			public:
				/**
				 * Default constructor
				 */
				NoMoreRows();
		};


		/** Unable to connect to the specified database server */
		class DBConnectionFailed:public Database{
			public:
				/**
				 * Default constructor
				 */
				DBConnectionFailed();
		};


		/** There was a sudden disconnection from the RDBMS */
		class ServerDisconnected:public Database{
			public:
				/**
				 * Default constructor
				 */
				ServerDisconnected();
		};


		/** Generic SQL query exception */
		class SQLQuery:public Database{
			public:
				/**
				 * Default constructor
				 */
				SQLQuery();
		};


		/** For some reason the server got disconnected while executing the underlying query. */
		class SQLQueryRDBMSDisconnected:public SQLQuery{
			public:
				/**
				 * Default constructor
				 */
				SQLQueryRDBMSDisconnected();
		};

		/** The SQL query sentece provide was not compatible or understandable
		 * to the RDBMS engine, please provide an appropiate SQL query with escape
		 * secuences were needed */
		class UnableToParseQuery:public SQLQuery{
			public:
				/**
				 * Default constructor
				 */
				UnableToParseQuery();
		};

		class BulkUploadFailed:public SQLQuery{
			public:
				/**
				 * Default constructor
				 */
				BulkUploadFailed();
		};

		class BulkDataParse:public SQLQuery{
			public:
				/**
				 * Default constructor
				 */
				BulkDataParse();
		};

		class BulkUploadStart:public SQLQuery{
			public:
				/**
				 * Default constructor
				 */
				BulkUploadStart();
		};
		
	};
};

#endif

