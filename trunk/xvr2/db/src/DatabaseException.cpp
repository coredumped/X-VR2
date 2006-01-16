/*
 * $Id$
 */
#include<xvr2/DatabaseException.h>
#include<xvr2/MessageStrings.h>

namespace xvr2 {
	namespace Exception {
#if GCC_MAJOR_VERSION < 3
		const char *_excepblkfn = "xvr2::BulkUploadFailed";
		const char *_excepblk_dpn = "xvr2::BulkDataParseFailed";
		const char *_excepblk_stn = "xvr2::BulkUploadStart";
#endif

		const char *_excepblkf = "Bulk data loading failed";
		const char *_excepblk_dp = "Bulk data parse error";
		const char *_excepblk_st = "Bulk load initialization error";

		Database::Database(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DatabaseException);
#endif
			description = (char *)xvr2::excepDatabaseException;
		}


		DBServerUnreachable::DBServerUnreachable(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DBServerUnreachableException);
#endif
			description = (char *)xvr2::excepDBServerUnreachable;
		}


		AlreadyConnected2DB::AlreadyConnected2DB(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2AlreadyConnected2DBException);
#endif
			description = (char *)xvr2::excepAlreadyConnected2DB;
		}


		DBConnectFirst::DBConnectFirst(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DBConnectFirstException);
#endif
			description = (char *)xvr2::excepDBConnectFirst;
		}

		NoDataFetch::NoDataFetch(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2NoDataFetchException);
#endif
			description = (char *)xvr2::excepNoDataFetch;
		}


		NoMoreRows::NoMoreRows(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2NoMoreRowsException);
#endif
			description = (char *)xvr2::excepNoMoreRows;
		}


		DBConnectionFailed::DBConnectionFailed(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2DBConnectionFailedException);
#endif
			description = (char *)xvr2::excepDBConnectionFailed;
		}


		ServerDisconnected::ServerDisconnected(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2ServerDisconnectedException);
#endif
			description = (char *)xvr2::excepServerDisconnected;
		}


		SQLQuery::SQLQuery(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2SQLQueryException);
#endif
			description = (char *)xvr2::excepSQLQuery;
		}


		SQLQueryRDBMSDisconnected::SQLQueryRDBMSDisconnected(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2SQLQueryRDBMSDisconnectedException);
#endif
			description = (char *)xvr2::excepSQLQueryRDBMSDisconnected;
		}


		UnableToParseQuery::UnableToParseQuery(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)xvr2::_xvr2UnableToParseQueryException);
#endif
			description = (char *)xvr2::excepUnableToParseQuery;
		}

		BulkUploadFailed::BulkUploadFailed():SQLQuery(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)_excepblkfn);
#endif
			description = (char *)_excepblkf;
		}

		BulkDataParse::BulkDataParse():SQLQuery(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)_excepblk_dpn);
#endif
			description = (char *)_excepblk_dp;
		}


		BulkUploadStart::BulkUploadStart():SQLQuery(){
#if GCC_MAJOR_VERSION < 3
			setClassName((char *)_excepblk_stn);
#endif
			description = (char *)_excepblk_st;
		}
	};
};


