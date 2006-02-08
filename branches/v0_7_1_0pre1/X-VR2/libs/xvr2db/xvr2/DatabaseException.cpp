/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/_xvr2dbClassNames.h>
#include<xvr2/DatabaseException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace DB {
		const char *_excepblkf = "Bulk data loading failed";
		const char *_excepblk_dp = "Bulk data parse error";
		const char *_excepblk_st = "Bulk load initialization error";

		DatabaseException::DatabaseException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DatabaseException);
#endif
			description = (char *)xvr2::excepDatabaseException;
		}


		DBServerUnreachable::DBServerUnreachable(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DBServerUnreachableException);
#endif
			description = (char *)xvr2::excepDBServerUnreachable;
		}


		AlreadyConnected2DB::AlreadyConnected2DB(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_AlreadyConnected2DBException);
#endif
			description = (char *)xvr2::excepAlreadyConnected2DB;
		}


		DBConnectFirst::DBConnectFirst(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DBConnectFirstException);
#endif
			description = (char *)xvr2::excepDBConnectFirst;
		}

		NoDataFetch::NoDataFetch(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_NoDataFetchException);
#endif
			description = (char *)xvr2::excepNoDataFetch;
		}


		NoMoreRows::NoMoreRows(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_NoMoreRowsException);
#endif
			description = (char *)xvr2::excepNoMoreRows;
		}


		DBConnectionFailed::DBConnectionFailed(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DBConnectionFailedException);
#endif
			description = (char *)xvr2::excepDBConnectionFailed;
		}


		ServerDisconnected::ServerDisconnected(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_ServerDisconnectedException);
#endif
			description = (char *)xvr2::excepServerDisconnected;
		}


		SQLQueryException::SQLQueryException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_SQLQueryException);
#endif
			description = (char *)xvr2::excepSQLQuery;
		}


		SQLQueryRDBMSDisconnected::SQLQueryRDBMSDisconnected(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_SQLQueryRDBMSDisconnectedException);
#endif
			description = (char *)xvr2::excepSQLQueryRDBMSDisconnected;
		}


		UnableToParseQuery::UnableToParseQuery(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_UnableToParseQueryException);
#endif
			description = (char *)xvr2::excepUnableToParseQuery;
		}

		BulkUploadFailed::BulkUploadFailed():SQLQueryException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_BulkUploadFailed);
#endif
			description = (char *)_excepblkf;
		}

		BulkDataParse::BulkDataParse():SQLQueryException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_BulkDataParse);
#endif
			description = (char *)_excepblk_dp;
		}


		BulkUploadStart::BulkUploadStart():SQLQueryException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_BulkUploadStart);
#endif
			description = (char *)_excepblk_st;
		}
	};
};

