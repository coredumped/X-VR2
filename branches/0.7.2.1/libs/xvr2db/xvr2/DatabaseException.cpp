/*
 * $Id$
 */
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/_xvr2dbClassNames.h>
#include<xvr2/MessageStrings.h>
#include"DatabaseException.h"
#include"DBResultSet.h"

namespace xvr2 {
	namespace DB {
		const char *_excepblkf = "Bulk data loading failed";
		const char *_excepblk_dp = "Bulk data parse error";
		const char *_excepblk_st = "Bulk load initialization error";
		const char *_excepblk_dn_st = "Bulk downloadload initialization error";
		const char *_excepblkf_dn = "Bulk data downloading failed";

		DatabaseException::DatabaseException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DatabaseException);
#endif
			description = (char *)xvr2::excepDatabaseException;
		}

		DatabaseException::DatabaseException(const String &error_message){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DatabaseException);
#endif
			description = (char *)error_message.toCharPtr();
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
		
		DBConnectionFailed::DBConnectionFailed(const String &_errmsg, const String &__host, 
										   const String &__db, const String &__user, 
										   const String &__pwd, int __port){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DBConnectionFailedException);
#endif
			description = (char *)_errmsg.toCharPtr();
			_host = __host;
			_user = __user;
#ifdef REVEAL_SENSITIVE_INFORMATION
			_pwd = __pwd;
#else
			_pwd = "*hidden*";
#endif
			_dbname = __db;
			_port = __port;
		}
		
		const String &DBConnectionFailed::host() const {
			return _host;
		}
		
		const int DBConnectionFailed::port() const {
			return _port;
		}
		
		const String &DBConnectionFailed::dbname() const {
			return _dbname;
		}
		
		const String &DBConnectionFailed::user() const {
			return _user;
		}
		
		const String &DBConnectionFailed::password() const {
			return _pwd;
		}

		ServerDisconnected::ServerDisconnected(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_ServerDisconnectedException);
#endif
			description = (char *)xvr2::excepServerDisconnected;
		}

#ifdef USE_EMBEDDED_CLASSNAMES
		static const char *__xvr2_DB_DBFieldIsNull = "xvr2::DB::FieldIsNull";
#endif

		FieldIsNull::FieldIsNull(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DBFieldIsNull);
#endif
		}

		FieldIsNull::FieldIsNull(const String &fn){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_DBFieldIsNull);
#endif
			field_name = fn;
		}

		const String &FieldIsNull::fieldName(){
			return field_name;
		}

		SQLQueryException::SQLQueryException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_SQLQueryException);
#endif
			description = (char *)xvr2::excepSQLQuery;
			result = 0;
		}

		SQLQueryException::SQLQueryException(const char *msg){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_SQLQueryException);
#endif
			description = (char *)msg;
			result = 0;
		}

		SQLQueryException::SQLQueryException(const char *msg, DB::ResultSet *_result, const String &__query){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_SQLQueryException);
#endif
			description = (char *)msg;
			result = _result;
			_query = __query;
		}

		SQLQueryException::SQLQueryException(const char *msg, const String &__query){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_SQLQueryException);
#endif
			description = (char *)msg;
			result = 0;
			_query = __query;
		}
		const String &SQLQueryException::query(){
			return _query;
		}
		SQLQueryException::SQLQueryException(const char *msg, DB::ResultSet *_result){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_SQLQueryException);
#endif
			description = (char *)msg;
			result = _result;
		}
		SQLQueryException::~SQLQueryException(){
			if(result != 0){
				//result->
			}
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

#ifdef USE_EMBEDDED_CLASSNAMES
		static const char *__xvr2_DB_BulkDownloadStart = "xvr2::DB::BulkDownloadStart";
#endif
		
		BulkDownloadStart::BulkDownloadStart(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_BulkDownloadStart);
#endif
			description = (char *)_excepblk_dn_st;			
		}
		
		BulkDownloadStart::BulkDownloadStart(const xvr2::String &__tablename, 
											 const xvr2::String &__cols, 
											 const xvr2::String &__error) : SQLQueryException(__error.toCharPtr()) {
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_BulkDownloadStart);
#endif
			description = (char *)_excepblk_dn_st;
			_tname = __tablename;
			_tcols = __cols;
		}
		BulkDownloadStart::BulkDownloadStart(const xvr2::String &__query, 
											 const xvr2::String &__tablename, 
											 const xvr2::String &__cols, 
											 const xvr2::String &__error) : SQLQueryException(__error.toCharPtr(), __query) {
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_BulkDownloadStart);
#endif
			description = (char *)_excepblk_dn_st;
			_tname = __tablename;
			_tcols = __cols;
		}
		
		const String &BulkDownloadStart::tablename(){
			return _tname;
		}
		
		const String &BulkDownloadStart::columns(){
			return _tcols;
		}
		
#ifdef USE_EMBEDDED_CLASSNAMES
		static const char *__xvr2_DB_BulkDownloadFailed = "xvr2::DB::BulkDownloadFailed";
#endif
		BulkDownloadFailed::BulkDownloadFailed():SQLQueryException(){
#ifdef USE_EMBEDDED_CLASSNAMES
			setClassName((char *)__xvr2_DB_BulkDownloadFailed);
#endif
			description = (char *)_excepblkf_dn;
		}
	};
};
