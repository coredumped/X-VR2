#include<xvr2.h>

using namespace xvr2;

#define DRIVER_LOCATION  __XVR2_PREFIX_DIR "/lib/xvr2/mysql_driver.so"
#define SELECT_STATEMENT "select * from users"
static const char *SS_TYPES[] = {
	"NOTYPE",
	"TINYINT",
	"INTEGER",
	"BIGINT",
	"FLOAT",
	"DOUBLE",
	"CHAR",
	"VARCHAR",
	"STRING",
	"BLOB",
	"TEXT0",
	"DATE1",
	"TIME",
	"TIMESTAMP",
	"BIT",
	"BYTE"
};

int main(){
	DB::Driver *drv;
	DB::Connection *conn = 0;
	DB::DriverInfo *q = 0;
	DB::ResultSet *r = 0;
	void *dbhandle;
	int ci,
 cj;
	drv = new DB::Driver(DRIVER_LOCATION);
	try{
		drv->load();
	}
	catch(Exception::DSOSymbol e){
		std::cerr << e.getClassName() << ": " << e.toString() << std::endl;
		return 1;
	}
	drv->getVersionInfo(&q);
	std::cout << "eSolutions4All MySQL driver " << q->version() << "." << q->revision() << " by: " << ((String *)&q->vendor())->toCharPtr() << " using: MySQL client " << ((String *)&q->description())->toCharPtr() << std::endl;

	conn = new DB::Connection(drv, "localhost", "mysql", "root", "", 3306);

	std::cout << "\n1. Connecting to database... ";
	std::cout.flush();
	try{
		conn->connect();
	}
	catch(...){
		std::cout << "failed" << std::endl;
		return 1;
	}
	std::cout << "succeeded" << std::endl;

/******  BEGIN QUERY *******/
	std::cout << "\n2. Querying database with \"" << SELECT_STATEMENT << "\"... ";
	try{
		//r = conn->query("select name from sections");
		r = conn->query(SELECT_STATEMENT);
	}
	catch(Exception::Exception e){
		std::cout << "failed" << std::endl;
		std::cerr << e.toString() << std::endl;
		return 1;
	}
	std::cout << "suceeded" << std::endl;

	std::cout << "Number of columns: " << r->numCols() << std::endl;
	std::cout << "Number of rows: " << r->numRows() << std::endl << std::endl;

	std::cout << "\n3. Reading ResultSet... " << std::endl;
	bool capshown = false;
	for(ci = 0; ci < r->numRows(); ci++){
		DB::Field *ff = (DB::Field *)r->getRow();
		if(!capshown){
			for(cj = 0; cj < r->numCols(); cj++){
				std::cout << ((String *)&ff[cj].getFieldName())->toCharPtr() << "\t";
			}
			std::cout << std::endl;
			capshown = true;
		}
		/*for(cj = 0; cj < r->numCols(); cj++){
		//	std::cout << "\t[" << SS_TYPES[ff[cj].getDatatype()] << "]";
			std::cout << "\t" << ff[cj].toChar();
			std::cout.flush();
		}*/
		//std::cout << ff[0].toInteger();
		std::cout << ((DB::Field *)&r->get("id"))->toInteger();
		std::cout << "\t" << ff[1].toInteger();
		std::cout << "\t" << ff[2].toInteger();
		std::cout << "\t" << ff[3].toBit();
		std::cout << "\t\t" << ff[4].toChar();
		std::cout << std::endl;
		r->fetchNextRow();
	}
	std::cout << "suceeded" << std::endl;
/******  END QUERY *******/

	std::cout << "\n4. Disconnecting from database... ";
	std::cout.flush();
	try{
		conn->disconnect();
	}
	catch(...){
		std::cout << "failed" << std::endl;
		return 1;
	}
	std::cout << "succeeded" << std::endl;
	xvr2_delete(drv);
	xvr2_delete(conn);
	return 0;
}
