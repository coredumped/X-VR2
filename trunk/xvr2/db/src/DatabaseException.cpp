/*
 * $Id$
 */
#include<DatabaseException.h>
#include<MessageStrings.h>

namespace xvr2 {
	namespace Exception {
#ifndef USING_GCC3
		const char *_excepblkfn = "xvr2::BulkUploadFailed";
		const char *_excepblk_dpn = "xvr2::BulkDataParseFailed";
		const char *_excepblk_stn = "xvr2::BulkUploadStart";
#endif

		const char *_excepblkf = "Bulk data loading failed";
		const char *_excepblk_dp = "Bulk data parse error";
		const char *_excepblk_st = "Bulk load initialization error";

		Database::Database(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DatabaseException);
#endif
			description = (char *)xvr2::excepDatabaseException;
		}


		DBServerUnreachable::DBServerUnreachable(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DBServerUnreachableException);
#endif
			description = (char *)xvr2::excepDBServerUnreachable;
		}


		AlreadyConnected2DB::AlreadyConnected2DB(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2AlreadyConnected2DBException);
#endif
			description = (char *)xvr2::excepAlreadyConnected2DB;
		}


		DBConnectFirst::DBConnectFirst(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DBConnectFirstException);
#endif
			description = (char *)xvr2::excepDBConnectFirst;
		}

		NoDataFetch::NoDataFetch(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NoDataFetchException);
#endif
			description = (char *)xvr2::excepNoDataFetch;
		}


		NoMoreRows::NoMoreRows(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2NoMoreRowsException);
#endif
			description = (char *)xvr2::excepNoMoreRows;
		}


		DBConnectionFailed::DBConnectionFailed(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2DBConnectionFailedException);
#endif
			description = (char *)xvr2::excepDBConnectionFailed;
		}


		ServerDisconnected::ServerDisconnected(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2ServerDisconnectedException);
#endif
			description = (char *)xvr2::excepServerDisconnected;
		}


		SQLQuery::SQLQuery(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SQLQueryException);
#endif
			description = (char *)xvr2::excepSQLQuery;
		}


		SQLQueryRDBMSDisconnected::SQLQueryRDBMSDisconnected(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2SQLQueryRDBMSDisconnectedException);
#endif
			description = (char *)xvr2::excepSQLQueryRDBMSDisconnected;
		}


		UnableToParseQuery::UnableToParseQuery(){
#ifndef USING_GCC3
			setClassName((char *)xvr2::_xvr2UnableToParseQueryException);
#endif
			description = (char *)xvr2::excepUnableToParseQuery;
		}

		BulkUploadFailed::BulkUploadFailed():Database(){
#ifndef USING_GCC3
			setClassName((char *)_excepblkfn);
#endif
			description = (char *)_excepblkf;
		}

		BulkDataParse::BulkDataParse():Database(){
#ifndef USING_GCC3
			setClassName((char *)_excepblk_dpn);
#endif
			description = (char *)_excepblk_dp;
		}


		BulkUploadStart::BulkUploadStart():Database(){
#ifndef USING_GCC3
			setClassName((char *)_excepblk_stn);
#endif
			description = (char *)_excepblk_st;
		}
	};
};


