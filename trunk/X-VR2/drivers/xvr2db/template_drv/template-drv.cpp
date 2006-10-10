/* $Id*/
#include<RDBMS_HEADER.h>
#include"template-drv.h"

using namespace xvr2;
//using namespace xvr2::Exception;

//////// INSTANCE CREATION AND DESTRUCTION STARTS HERE /////////

DB_TemplateDriver *create_dbdriver_instance(){
	return new DB_TemplateDriver();
}

void destroy_dbdriver_instance(DB_TemplateDriver *obj){
	delete obj;
}

//////// INSTANCE CREATION AND DESTRUCTION ENDS HERE /////////


//////// SUPPORT CLASSES AND FUNCTIONS STARTS HERE /////////

class __rdbms_conn {
	public:
		RDBMS_INTERNAL_Conn_Structure *conn;

		__rdbms_conn(RDBMS_INTERNAL_Conn_Structure *_conn){
			conn = _conn;
		}

		~__rdbms_conn(){
			//Release connection structure resources here
		}

};

class __rdbms_result_set {
	public:
		RDBMS_INTERNAL_ResultSet_Structure *result;
		__rdbms_conn *conn;
		int curr_row;
		int row_count;
		__rdbms_result_set(RDBMS_INTERNAL_ResultSet_Structure *r){
			result = r;
			curr_row = 0;
			row_count = ;/* Insert funtion name that retrieves the 
				        amount of rows contained in this
				        resultset. */
		}
};
//////// SUPPORT CLASSES AND FUNCTIONS ENDS HERE /////////








DB_TemplateDriver::DB_TemplateDriver(){
	dinfo = new DB::DriverInfo(DRV_VERSION, DRV_REVISION, "INSERT AUTHOR NAME HERE", "INSERT INTERNAL RDBMS VERSION STRING");
	// Call any initialization routines needed by the underlying
	// RDBMS library to be wrapped
}

DB_TemplateDriver::~DB_TemplateDriver(){
	delete dinfo;
}

const DB::DriverInfo &DB_TemplateDriver::getVersionInfo(){
	return *dinfo;
}

////////////////////// CONNECT STARTS HERE /////////////////////
void *DB_TemplateDriver::connect(const String &server, const String &__dbname, const String &user, const String &pass, int port){
	//use this method to actually connect to the database via TCP/IP
	RDBMS_INTERNAL_Conn_Structure *conn;
	__rdbms_conn *connx;

	conn = /* Call RDBMS internal function to connect to the DB. */(server, __dbname, user, pass, port);

	connx = new __rdbms_conn(conn);
	return (void *)connx;

}
////////////////////// CONNECT ENDS HERE /////////////////////

ResultSet *DB_TemplateDriver::query(void *__conn_handle, const String &command){
	DB::ResultSet *r = 0;
	RDBMS_INTERNAL_ResultSet_Structure *result;
	__rdbms_result_set *rres;
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;

	result = /* RDBMS FUNCTION TO EXECUTE A QUERY*/ (conn->conn, command.toCharPtr());
	if(/* If resultset couldn't be executed at all */){
		throw DB::SQLQueryException(/* RDBMS ERROR STRING IN CASE OF FAILURE */);
	}
	else{
		/* Analyze resultset status */
		switch(/* Result set status value */){
			case /* RESULT SET IS FROM A SELECT, BUILD RESULT SET OBJECT ACCORDINGLY */:
				rres = new __rdbms_result_set(result);
				rres->conn = conn;
				r = new DB::ResultSet(this, (void *)rres, true);
				break;
			case /* RESULT SET IS FROM A NON RESULT-RETURNING STATEMENS, UPDATE, DELETE, ETC.*/:
				r = new DB::ResultSet(this, 0, true, /* AMOUNT OF AFFECTED ROWS AFTER THE STATEMENT COMPLETED */);
				/* RELEASE RESULT SET OBJECT */(result);
				break;
			default: //SOME SORT OF EXTRANGE ERROR OCURRED WHICH WAS NOT CAUGHT BY THE IF ABOVE
				r = new DB::ResultSet(this, (void *)rres, false);
				throw DB::SQLQueryException(/* SPECIFIC OPERATION ERROR MESSAGE RETURNED BY THE RDBMS */, r);
		}
	}
	return r;
}

bool DB_TemplateDriver::disconnect(void *__conn_handle){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	/* CLOSE RDBMS CONNECTION */(conn->conn);
	delete conn;
	return true;
}

void DB_TemplateDriver::setAutoCommit(bool){
	/* CALL SPECIFIC RDBMS FUNCTION TO SWITCH AUTO-COMMIT ON OR OFF, Oracle (tm) anyone? */
}

void DB_TemplateDriver::commit(void *){
	/* CALL SPECIFIC RDBMS FUNCTION TO COMMIT PREVIOUSLY ISSUED COMMANDS, Oracle (tm) anyone? */
}

const int DB_TemplateDriver::numRows(void *__res_handle){
	//Will return the number of rows in a query result
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	return r->row_count;
}

const int DB_TemplateDriver::numCols(void *__res_handle){
	//Will return the number of columns in a query result
	int n = 0;
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	n = /* RDBMS FUNCTION WHICH RETURN THE AMOUNT OF COLUMNS IN A RESULT SET */(r->result);
	return n;
}

Field *DB_TemplateDriver::fetchRow(void *__res_handle){
	//Will fetch the next row in a database
	DB::Field *s = 0;
	char *f;
	char *data;
	unsigned int num, n;
	int thetype;
	bool bdat;
	Int16 tint;
	Int32 iint;
	Int64 bint;
	float float4;
	double float8;
	xvr2::Date *tdate;
	xvr2::Time *ttime;
	xvr2::Timestamp *tstamp;
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	if(r->curr_row >= r->row_count)
		return 0;
	//Get the number of columns
	num = /* RDBMS FUNCTION WHICH RETURN THE AMOUNT OF COLUMNS IN A RESULT SET */(r->result);
	//Allocate the field array
	s = new DB::Field[num];
	//Open a loop to instatiate every data field
	for(n = 0; n < num; n++){
		f = /* FUNCTION WHICH RETURN THE NAME OF THE NTH COLUMN IN THE RESULT SET */(r->result, n);
		s[n].setFieldName(f);
		thetype = /* FIND A WAY TO GET THE FIELD TYPE MATCHING OUR ENUMS */

		/* * * WARNING: data must be a null terminated string!!!!!!! * * */

		data = /* GET THE VALUE STORED AT THE CURRENT CELL */(r->result, r->curr_row, n);
		if(/* IF THE CELL CONTENTS ARE NOT BINARY */){
			//DATA IS TEXT
			switch(thetype){
				case DB::Field::BIT:
					if(data[0] == 't' || strncasecmp(data, "true", 4) == 0 || strncasecmp(data, "1", 1) == 0){
						bdat = true;
						s[n].init(xvr2::DB::Field::BIT, (void *)&bdat, sizeof(bool));
					}
					else{
						bdat = false;
						s[n].init(xvr2::DB::Field::BIT, (void *)&bdat, sizeof(bool));
					}
					break;
				case DB::Field::TINYINT:
					tint = atoi(data);
					s[n].init(xvr2::DB::Field::TINYINT, (void *)&tint, sizeof(Int16));
					break;
				case DB::Field::INTEGER:
					iint = atol(data);
					s[n].init(xvr2::DB::Field::INTEGER, (void *)&iint, sizeof(Int32));
					break;
				case DB::Field::BIGINT:
					bint = atoll(data);
					s[n].init(xvr2::DB::Field::BIGINT, (void *)&bint, sizeof(Int64));
					break;
				case DB::Field::FLOAT:
					float4 = atof(data);
					s[n].init(xvr2::DB::Field::FLOAT, (void *)&float4, sizeof(float));
					break;
				case DB::Field::DOUBLE:
					float8 = atof(data);
					s[n].init(xvr2::DB::Field::DOUBLE, (void *)&float8, sizeof(double));
					break;
				case DB::Field::DATE:
					if(/* IF CURRENT CELL IS NOT NULL */(r->result, r->curr_row, n))
						tdate = new Date("%Y-%m-%d", data);
					else
						tdate = 0;
					s[n].init(xvr2::DB::Field::DATE, (void *)tdate, sizeof(xvr2::Date));
					xvr2_delete(tdate);
					break;
				case DB::Field::TIME:
					if(/* IF CURRENT CELL IS NOT NULL */(r->result, r->curr_row, n))
						ttime = new Time(data);
					else
						ttime = 0;
					s[n].init(xvr2::DB::Field::TIME, (void *)ttime, sizeof(xvr2::Time));
					xvr2_delete(ttime);
					break;
				case DB::Field::TIMESTAMP:
					if(/* IF CURRENT CELL IS NOT NULL */(r->result, r->curr_row, n))
						tstamp = new Timestamp("%Y-%m-%d %T", data);
					else
						tstamp = 0;
					s[n].init(xvr2::DB::Field::TIMESTAMP, (void *)tstamp, sizeof(xvr2::Timestamp));
					xvr2_delete(tstamp);
					break;
				case DB::Field::VARCHAR:
				default:
					if(/* IF CURRENT CELL IS NULL */(r->result, r->curr_row, n))
						s[n].init(xvr2::DB::Field::VARCHAR, (void *)0, /* OBTAIN CELL LENGHT CONTENTS */(r->result, r->curr_row, n) + 1);
					else
						s[n].init(xvr2::DB::Field::VARCHAR, (void *)data, /* OBTAIN CELL LENGHT CONTENTS */(r->result, r->curr_row, n) + 1);
			}
		}
		else{
			//DATA IS BINARY
			s[n].init(xvr2::DB::Field::BLOB, (void *)data, /* Get data length for current binary cell */(r->result, r->curr_row, n));
		}
	}
	r->curr_row++;
	return s;

}

const bool DB_TemplateDriver::freeResultSet(void *__res_handle){
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	/* Call RDBMS ResultSet resource memory-freeing function */(r->result);
	delete r;
	return true;
}

const bool DB_TemplateDriver::bulkBegin(void *conn_handle, const char *table, const char *columns, const char *delim){
	bool ret;
	RDBMS_INTERNAL_ResultSet_Structure *result;
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)conn_handle;
	
	result = /* CALL INTERNAL RDBMS BULK LOADING INITIALIZATION ROUTINE */
	if(result == NULL){
		throw DB::SQLQueryException(/* GET RDBMS ERROR STRING */(conn->conn));
	}
	switch(/* Result set status value */){
		case RBMS_BULK_INITIALIZATION_SUCCESS:
			ret = true;
			break;
		default:
			ret = false;
	}
	/* RELEASE THE RESULT SET OBJECT THEN */(result);
	return ret;
}

const bool DB_TemplateDriver::bulkAddData(void *conn_handle, const char *data, const char *delim){
	int ret;
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)conn_handle;
	ret = /* CALL RDBMS BULK DATA UPLOADING FUNCTION */(conn->conn, data, strlen(data));
	if(ret == 1)
		return true;
	else if(ret == -1){
		throw DB::SQLQueryException(/* GET RDBMS ERROR STRING */ (conn->conn));
	}
	return false;
}

const bool DB_TemplateDriver::bulkEnd(void *conn_handle){
	int ret;
	RDBMS_INTERNAL_ResultSet_Structure *result;
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)conn_handle;
	ret = /* CAL RDBMS INTERNAL BULK DATA UPLOAD FINALIZATION FUNCTION */(conn->conn, NULL);
	if(ret == 1){
		result = /* GET RDBMS RESULT SET */(conn->conn);
		if(result == NULL){
			throw DB::SQLQueryException(/* GET RDBMS ERROR STRING */(conn->conn));
		}
		else {
			if(/* IF RESULTSET STATUS IS SUCCESSFULL */){
				/* FREE RESULTSET OBJECT */(result);
				return true;
			}
			/* FREE RESULTSET OBJECT */(result);
		}
	}
	throw DB::SQLQueryException(/* GET RDBMS ERROR STRING */(conn->conn));
	return false;
}

char *DB_TemplateDriver::quoteString(const char *in){
	char *buf;
	int len;
	len = strlen(in);
	buf = new char(len * 2 + 1);
	/* CALL RDBMS INTERNAL STRING ESCAPING FUNCTION */(buf, in, len);
	return buf;
}

String DB_TemplateDriver::escapeString(const String &s){
	char buf[s.size() * 2 + 1];
	/* CALL RDBMS INTERNAL STRING ESCAPING FUNCTION */(buf, s.toCharPtr(), s.size());
	return String(buf);
}

String DB_TemplateDriver::escapeString(const String &s, void *__conn_handle){
	__rdbms_conn *conn;
	int e_code;
	char buf[s.size() * 2 + 1];
	conn = (__rdbms_conn *)__conn_handle;
	/* CALL RDBMS INTERNAL STRING ESCAPING FUNCTION */(conn->conn, buf, s.toCharPtr(), s.size(), &e_code);
	if(e_code != 0){
		//Houston we have a problem
		throw DB::DatabaseException(/* GET RDBMS ERROR STRING */(conn->conn));
	}
	return String(buf);
}

const char *DB_TemplateDriver::errorMessage(void *__conn_handle){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	return /* GET RDBMS ERROR STRING */(conn->conn);
}

const char *DB_TemplateDriver::resultErrorMessage(void *__res_handle){
	__rdbms_result_set *r;
	r = (__rdbms_result_set *)__res_handle;
	return /* GET RDBMS SPECIFIC RESULTSET ERROR STRING */(r->result);
}

const bool DB_TemplateDriver::isConnected(void *__conn_handle){
	__rdbms_conn *conn;
	conn = (__rdbms_conn *)__conn_handle;
	return /* CALL RDBMS SPECIFIC CONNECTION STATUS QUERY FUNCTION */(conn->conn) == RDBMS_CONNECTION_IS_OK ? true : false;
}

const bool DB_TemplateDriver::hasConnPolling(){
	/* If there exists a function in thi driver to check connection status */
	return true;
}
