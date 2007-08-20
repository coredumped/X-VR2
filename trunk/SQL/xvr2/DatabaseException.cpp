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
#include"config.h"
#include<xvr2/xvr2config.h>
#include<xvr2/MessageStrings.h>
#include"DatabaseException.h"
#include"ResultSet.h"

namespace xvr2 {
	namespace SQL {
		static const char *_excepblkf = "Bulk data loading failed";
		static const char *_excepblk_dp = "Bulk data parse error";
		static const char *_excepblk_st = "Bulk load initialization error";
		static const char *_noop_ex = "Requested operation is not supported at driver level.";

		DatabaseException::ConnectionParams::ConnectionParams(){
			port = -1;
			type = DatabaseException::NET;
		}
		DatabaseException::ConnectionParams::ConnectionParams(
								DatabaseException::ConnectionType t,
								const String &h, int p, const String &db,
								const String &u, const String &_p,
								const String &_path){
			type = t;
			host = h;
			port = p;
			database = db;
			username = u;
			password = _p;
			path = _path;
		}
		DatabaseException::ConnectionParams::ConnectionParams(
				const ConnectionParams &c){
			type = c.type;
			host = c.host;
			port = c.port;
			database = c.database;
			username = c.username;
			password = c.password;
			path = c.path;
		}
		DatabaseException::ConnectionParams &DatabaseException::ConnectionParams::operator=(
				const ConnectionParams &c){
			type = c.type;
			host = c.host;
			port = c.port;
			database = c.database;
			username = c.username;
			password = c.password;
			path = c.path;
			return *this;
		}
		
		
		DatabaseException::DatabaseException(){
			description = (char *)xvr2::excepDatabaseException;
		}

		DatabaseException::DatabaseException(const String &error_message){
			description = (char *)error_message.toCharPtr();
			_err_msg = error_message;
		}
		
		DatabaseException::DatabaseException(const String &error_message, 
							const DatabaseException::ConnectionParams &__conn_p){
			_conn_params = __conn_p;
			_err_msg = error_message;
		}
		
		DatabaseException::DatabaseException( 
									const DatabaseException::ConnectionParams &__conn_p){
			_conn_params = __conn_p;
		}
		
		const DatabaseException::ConnectionParams &DatabaseException::connParams(){
			return _conn_params;
		}
		
		const String &DatabaseException::errorMessage(){
			return _err_msg;
		}
		
		DriverOperationNotSupported::DriverOperationNotSupported(){
			description = (char *)_noop_ex;
		}

		DriverOperationNotSupported::DriverOperationNotSupported(
				const String &_op){
			description = (char *)_noop_ex;
			op = _op;
		}
		
		const String &DriverOperationNotSupported::operation(){
			return op;
		}

		DBServerUnreachable::DBServerUnreachable(){
			description = (char *)xvr2::excepDBServerUnreachable;
		}


		AlreadyConnected2DB::AlreadyConnected2DB(){
			description = (char *)xvr2::excepAlreadyConnected2DB;
		}


		DBConnectFirst::DBConnectFirst(){
			description = (char *)xvr2::excepDBConnectFirst;
		}

		NoDataFetch::NoDataFetch(){
			description = (char *)xvr2::excepNoDataFetch;
		}


		NoMoreRows::NoMoreRows(){
			description = (char *)xvr2::excepNoMoreRows;
		}


		DBConnectionFailed::DBConnectionFailed(){
			description = (char *)xvr2::excepDBConnectionFailed;
		}
		
		ConnectionFailure::ConnectionFailure(){
			
		}
		
		ConnectionFailure::ConnectionFailure(const ConnectionParams &__conn_p):DatabaseException(__conn_p){
			
		}
		
		ConnectionFailure::ConnectionFailure(const ConnectionParams &__conn_p, 
							const String &__cause){
			_err_msg = __cause;
		}

		ServerDisconnected::ServerDisconnected(){
			description = (char *)xvr2::excepServerDisconnected;
		}

		FieldIsNull::FieldIsNull(){

		}

		FieldIsNull::FieldIsNull(const String &fn){

			field_name = fn;
		}

		const String &FieldIsNull::fieldName(){
			return field_name;
		}

		SQLQueryException::SQLQueryException(){
			description = (char *)xvr2::excepSQLQuery;
			result = 0;
		}

		SQLQueryException::SQLQueryException(const char *msg):DatabaseException(msg){
			description = (char *)msg;
			result = 0;
		}

		SQLQueryException::SQLQueryException(const char *msg, SQL::ResultSet *_result, const String &__query):DatabaseException(msg){
			description = (char *)msg;
			result = _result;
			_query = __query;
		}

		SQLQueryException::SQLQueryException(const char *msg, const String &__query):DatabaseException(msg){
			description = (char *)msg;
			result = 0;
			_query = __query;
		}
		const String &SQLQueryException::query(){
			return _query;
		}
		SQLQueryException::SQLQueryException(const char *msg, SQL::ResultSet *_result):DatabaseException(msg){
			description = (char *)msg;
			result = _result;
		}
		SQLQueryException::~SQLQueryException(){
			if(result != 0){
				//result->
			}
		}

		SQLQueryRDBMSDisconnected::SQLQueryRDBMSDisconnected(){
			description = (char *)xvr2::excepSQLQueryRDBMSDisconnected;
		}


		UnableToParseQuery::UnableToParseQuery(){
			description = (char *)xvr2::excepUnableToParseQuery;
		}

		BulkUploadFailed::BulkUploadFailed():SQLQueryException(){
			description = (char *)_excepblkf;
		}

		BulkDataParse::BulkDataParse():SQLQueryException(){
			description = (char *)_excepblk_dp;
		}


		BulkUploadStart::BulkUploadStart():SQLQueryException(){
			description = (char *)_excepblk_st;
		}
	};
};
